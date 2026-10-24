#!/usr/bin/env bash

# Apache License 2.0

# Build and install yaml-cpp as a static, position-independent library into ${INSTALL_PREFIX}.

set -euo pipefail

YAML_CPP_VERSION="0.7.0"
prefix="${INSTALL_PREFIX:-/usr/local}"

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

git clone --branch "yaml-cpp-${YAML_CPP_VERSION}" --depth 1 https://github.com/jbeder/yaml-cpp.git "${source_dir}"

cmake -S "${source_dir}" -B "${source_dir}/build" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${prefix}" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DYAML_BUILD_SHARED_LIBS=OFF \
    -DYAML_CPP_BUILD_TESTS=OFF
cmake --build "${source_dir}/build" --parallel "$(getconf _NPROCESSORS_ONLN)"
cmake --install "${source_dir}/build"
