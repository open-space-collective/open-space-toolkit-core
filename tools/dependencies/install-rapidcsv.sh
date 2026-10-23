#!/usr/bin/env bash

# Apache License 2.0

# Install Rapidcsv headers into ${INSTALL_PREFIX}/include/rapidcsv.

set -euo pipefail

RAPIDCSV_VERSION="6.11"
prefix="${INSTALL_PREFIX:-/usr/local}"

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

git clone --branch "v${RAPIDCSV_VERSION}" --depth 1 https://github.com/d99kris/rapidcsv.git "${source_dir}"

mkdir -p "${prefix}/include/rapidcsv"
cp "${source_dir}/src/"*.h "${prefix}/include/rapidcsv/"
