#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/ci/test.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

project_directory="${script_directory}"/../..

docker run \
--rm \
--volume="${project_directory}:/app:rw" \
--volume="/app/build" \
--volume="${project_directory}/docker/environment/helpers/build.sh:/app/build/build.sh:ro" \
--volume="${project_directory}/docker/environment/helpers/test.sh:/app/build/test.sh:ro" \
--workdir="/app/build" \
"openspacecollective/library-core:latest" \
"/bin/bash -c '/app/build/build.sh'"

################################################################################################################################################################