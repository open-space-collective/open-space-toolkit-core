#!/usr/bin/env bash

# Apache License 2.0

# Install all dependencies into ${INSTALL_PREFIX}.

set -euo pipefail

dependencies_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

"${dependencies_dir}/install-rapidjson.sh"
"${dependencies_dir}/install-yaml-cpp.sh"
"${dependencies_dir}/install-ordered-map.sh"
"${dependencies_dir}/install-fmt.sh"
"${dependencies_dir}/install-rapidcsv.sh"
