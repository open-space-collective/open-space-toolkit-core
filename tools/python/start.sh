#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/python/start.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

source ../.env

if [[ ! -z $1 ]] && [[ $1 == "--link" ]]; then

    docker run \
    --name="${container_name}-notebook" \
    -it \
    --rm \
    --publish="8886:8888" \
    --user="" \
    --env="JUPYTER_ENABLE_LAB=yes" \
    --env="LD_LIBRARY_PATH=/usr/local/lib:/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --env="PYTHONPATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --volume=$(pwd)/../../../library-physics/lib:/opt/library-physics:ro \
    --volume=$(pwd)/../../lib:/opt/lib:ro \
    --volume=$(pwd)/../../share/python/notebooks:/home/jovyan/notebooks \
    --workdir="/home/jovyan/notebooks" \
    "${repository_name}/${project_name}-python" \
    bash -c "mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Core \
    && ln -s /opt/lib/liblibrary-core.so.0 /opt/conda/lib/python3.6/site-packages/Library/Core/liblibrary-core.so.0 \
    && ln -s /opt/lib/LibraryCorePy.so /opt/conda/lib/python3.6/site-packages/Library/Core/LibraryCorePy.so \
    && echo 'from .LibraryCorePy import *' > /opt/conda/lib/python3.6/site-packages/Library/Core/__init__.py \
    && start-notebook.sh --NotebookApp.token=''"

    # && ln -s /opt/lib/libboost_python36.so.1.68.0 /opt/conda/lib/python3.6/site-packages/Library/Core/libboost_python36.so.1.68.0 \

else

    docker run \
    --name="${container_name}-notebook" \
    -it \
    --rm \
    --publish="8886:8888" \
    --user="" \
    --env="JUPYTER_ENABLE_LAB=yes" \
    --env="LD_LIBRARY_PATH=/usr/local/lib:/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --env="PYTHONPATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --volume=$(pwd)/../../share/python/notebooks:/home/jovyan/notebooks \
    --workdir="/home/jovyan/notebooks" \
    "${repository_name}/${project_name}-python" \
    bash -c "start-notebook.sh --NotebookApp.token=''"

fi

popd > /dev/null

################################################################################################################################################################