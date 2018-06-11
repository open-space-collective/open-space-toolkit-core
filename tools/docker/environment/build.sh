#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/docker/environment/build.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source "${script_directory}/../setup.sh"

echo "version = ${version}"
echo "cpu_count = ${cpu_count}"
echo "image_name = ${image_name}"
echo "script_directory = ${script_directory}"

docker build \
--build-arg="version=${version}" \
--build-arg="cpu_count=${cpu_count}" \
--tag="${image_name}" \
--file="${script_directory}/Dockerfile" \
"${script_directory}"

################################################################################################################################################################