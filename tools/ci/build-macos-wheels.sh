#!/usr/bin/env bash

# Apache License 2.0

# Build Apple Silicon wheels for open-space-toolkit-core.
# Dependencies are installed with the tools/dependencies scripts, as in docker/development/Dockerfile.
# Homebrew Boost is linked dynamically and vendored with delocate.

set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
prefix="${root}/.macos-deps"
build_dir="${root}/build-macos"
packages_dir="${root}/packages/python"

export HOMEBREW_NO_AUTO_UPDATE=1
export NONINTERACTIVE=1
# Homebrew Python links extensions with a bare `clang -bundle`, which fails on the source-less _platform extension.
export UV_PYTHON_PREFERENCE=only-managed
unset VIRTUAL_ENV

if [[ "$(uname -s)" != "Darwin" ]]; then
    echo "macOS wheels must be built on Darwin."
    exit 1
fi

if [[ "$(uname -m)" != "arm64" ]]; then
    echo "This script builds Apple Silicon (arm64) wheels. The current machine is $(uname -m)."
    exit 1
fi

if ! command -v brew >/dev/null 2>&1; then
    echo "Homebrew is required."
    exit 1
fi

export PATH="$(brew --prefix)/bin:${HOME}/.local/bin:${PATH}"

if ! command -v uv >/dev/null 2>&1; then
    curl -LsSf https://astral.sh/uv/install.sh | sh
    export PATH="${HOME}/.local/bin:${PATH}"
fi

brew install cmake boost

deployment_target="${MACOSX_DEPLOYMENT_TARGET:-14.0}"
boost_library="$(find "$(brew --prefix boost)/lib" -name 'libboost_filesystem.dylib' -print -quit)"
if [[ -n "${boost_library}" ]]; then
    boost_minos="$(otool -l "${boost_library}" | awk '/minos/ { print $2; exit }')"
fi
if [[ -n "${boost_minos:-}" ]]; then
    deployment_target="$(
        deployment_target="${deployment_target}" boost_minos="${boost_minos}" python3 - <<'PY'
import os

def version(value):
    return tuple(int(part) for part in value.split("."))

chosen = os.environ["deployment_target"]
boost = os.environ["boost_minos"]
print(boost if version(boost) > version(chosen) else chosen)
PY
    )"
    if [[ "${deployment_target}" != "${MACOSX_DEPLOYMENT_TARGET:-14.0}" ]]; then
        echo "Homebrew Boost requires macOS ${boost_minos}. The wheel deployment target is ${deployment_target}."
    fi
fi
export MACOSX_DEPLOYMENT_TARGET="${deployment_target}"
# CMake 4 dropped compatibility with projects that declare cmake_minimum_required below 3.5.
# yaml-cpp 0.7.0 and this repository still declare an older minimum.
export CMAKE_POLICY_VERSION_MINIMUM=3.5

if [[ ! -f "${prefix}/.installed" ]]; then
    INSTALL_PREFIX="${prefix}" "${root}/tools/dependencies/install.sh"
    touch "${prefix}/.installed"
fi

tool_venv="${prefix}/tool-venv"
if [[ ! -x "${tool_venv}/bin/python" ]]; then
    uv venv "${tool_venv}" --python 3.12
fi
uv pip install --python "${tool_venv}/bin/python" "pybind11>=2.12" delocate
pybind11_dir="$("${tool_venv}/bin/python" -c 'import pybind11; print(pybind11.get_cmake_dir())')"

installed_versions=()
for version in 3.9 3.10 3.11 3.12 3.13 3.14; do
    if uv python install "${version}"; then
        installed_versions+=("${version}")
    elif [[ "${version}" == "3.9" ]]; then
        echo "Python 3.9 has no build for this macOS. Skipping it."
    else
        echo "Failed to install Python ${version}."
        exit 1
    fi
done

python_search_versions="$(IFS=';'; echo "${installed_versions[*]}")"

export CPATH="${prefix}/include${CPATH:+:${CPATH}}"

rm -rf "${build_dir}"
cmake -S "${root}" -B "${build_dir}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_PREFIX_PATH="${prefix};$(brew --prefix)" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET="${MACOSX_DEPLOYMENT_TARGET}" \
    -Dpybind11_DIR="${pybind11_dir}" \
    -DPYTHON_SEARCH_VERSIONS="${python_search_versions}" \
    -DBUILD_WITH_DEBUG_SYMBOLS=OFF \
    -DBUILD_UNIT_TESTS=OFF \
    -DBUILD_PYTHON_BINDINGS=ON \
    -DBUILD_DOCUMENTATION=OFF \
    -DBUILD_WITH_BOOST_STACKTRACE=OFF \
    -DBUILD_WITH_BOOST_STATIC=OFF
cmake --build "${build_dir}" --parallel "$(sysctl -n hw.ncpu)"

mkdir -p "${packages_dir}"
rm -f "${packages_dir}"/*.whl
shopt -s nullglob
wheels=("${build_dir}/bindings/python/dist/"*.whl)
if [[ ${#wheels[@]} -eq 0 ]]; then
    echo "CMake did not produce any wheels."
    exit 1
fi

for wheel in "${wheels[@]}"; do
    "${tool_venv}/bin/delocate-wheel" --require-archs arm64 -w "${packages_dir}" "${wheel}"
done

for wheel in "${packages_dir}"/*.whl; do
    dependencies="$("${tool_venv}/bin/delocate-listdeps" --all "${wheel}" || true)"
    if grep -E '/opt/homebrew|/usr/local' <<<"${dependencies}"; then
        echo "Wheel still depends on libraries outside the archive: ${wheel}"
        exit 1
    fi
done

smoke_wheel="$(echo "${packages_dir}"/*cp314-cp314-*.whl)"
smoke_venv="${prefix}/smoke-venv"
rm -rf "${smoke_venv}"
uv venv "${smoke_venv}" --python 3.14
uv pip install --python "${smoke_venv}/bin/python" "${smoke_wheel}"
"${smoke_venv}/bin/python" -c 'import ostk.core'

echo "macOS wheels are in ${packages_dir}"
