#!/usr/bin/env bash

# Apache License 2.0

# Install RapidJSON headers into ${INSTALL_PREFIX}.

set -euo pipefail

RAPIDJSON_VERSION="master"
prefix="${INSTALL_PREFIX:-/usr/local}"

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

git clone --branch "${RAPIDJSON_VERSION}" --depth 1 https://github.com/Tencent/rapidjson.git "${source_dir}"

mkdir -p "${prefix}/include"
cp -R "${source_dir}/include/rapidjson" "${prefix}/include/"
