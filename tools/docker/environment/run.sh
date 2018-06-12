#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/docker/environment/run.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source "${script_directory}/../.env"

docker run \
--name="${container_name}" \
-it \
--rm \
--privileged \
--volume="${project_directory}:/app:rw" \
--volume="/app/build" \
--volume="${script_directory}/helpers/build.sh:/app/build/build.sh:ro" \
--volume="${script_directory}/helpers/test.sh:/app/build/test.sh:ro" \
--volume="${script_directory}/helpers/debug.sh:/app/build/debug.sh:ro" \
--volume="${script_directory}/helpers/clean.sh:/app/build/clean.sh:ro" \
--workdir="/app/build" \
"${image_name}" \
"/bin/bash"

################################################################################################################################################################