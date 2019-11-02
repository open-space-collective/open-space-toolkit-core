#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Core
# @file           tools/python/start.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

source "../.env"

# Build Docker image if it does not exist already

if [[ "$(docker images -q ${image_name}-python:${image_version} 2> /dev/null)" == "" ]]; then

    pushd "${script_directory}/docker" > /dev/null

    ./build.sh

    popd > /dev/null

fi

if [[ ! -z $1 ]] && [[ $1 == "--link" ]]; then

    docker run \
    --name="${container_name}-notebook" \
    -it \
    --rm \
    --publish="${python_port}:8888" \
    --user="" \
    --env="JUPYTER_ENABLE_LAB=yes" \
    --env="LD_LIBRARY_PATH=/usr/local/lib:/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib" \
    --env="PYTHONPATH=/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib" \
    --volume="${project_directory}/lib:/opt/lib:ro" \
    --volume="${project_directory}/bindings/python/docs:/home/jovyan/docs" \
    --volume="${project_directory}/tutorials/python/notebooks:/home/jovyan/tutorials" \
    --workdir="/home/jovyan" \
    "${image_name}-python:${image_version}" \
    bash -c "mkdir -p /opt/conda/lib/python3.7/site-packages/Library/Core \
    && ln -s /opt/lib/liblibrary-core.so.0 /opt/conda/lib/python3.7/site-packages/Library/Core/liblibrary-core.so.0 \
    && ln -s /opt/lib/LibraryCorePy.so /opt/conda/lib/python3.7/site-packages/Library/Core/LibraryCorePy.so \
    && echo 'from .LibraryCorePy import *' > /opt/conda/lib/python3.7/site-packages/Library/Core/__init__.py \
    && start-notebook.sh --NotebookApp.token=''"

    # && ln -s /opt/lib/libboost_python37.so.1.70.0 /opt/conda/lib/python3.7/site-packages/Library/Core/libboost_python37.so.1.70.0 \

else

    # docker run \
    # --name="${container_name}-notebook" \
    # -it \
    # --rm \
    # --publish="${python_port}:8888" \
    # --user="" \
    # --env="JUPYTER_ENABLE_LAB=yes" \
    # --env="LD_LIBRARY_PATH=/usr/local/lib:/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib" \
    # --env="PYTHONPATH=/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib" \
    # --volume="${project_directory}/lib:/opt/lib:ro" \
    # --volume="${project_directory}/bindings/python/docs:/home/jovyan/docs" \
    # --volume="${project_directory}/tutorials/python/notebooks:/home/jovyan/tutorials" \
    # --workdir="/home/jovyan" \
    # "${image_name}-python:${image_version}" \
    # bash -c "mkdir -p /opt/conda/lib/python3.7/site-packages/Library/Core \
    # && ln -s /opt/lib/liblibrary-core.so.0 /opt/conda/lib/python3.7/site-packages/Library/Core/liblibrary-core.so.0 \
    # && ln -s /opt/lib/LibraryCorePy.so /opt/conda/lib/python3.7/site-packages/Library/Core/LibraryCorePy.so \
    # && echo 'from .LibraryCorePy import *' > /opt/conda/lib/python3.7/site-packages/Library/Core/__init__.py \
    # && start-notebook.sh --NotebookApp.token=''"

    docker run \
    --name="${container_name}-notebook" \
    -it \
    --rm \
    --publish="${python_port}:8888" \
    --user="root" \
    --env-file="${script_directory}/.env" \
    --volume="${project_directory}/bindings/python/docs:/home/jovyan/docs" \
    --volume="${project_directory}/tutorials/python/notebooks:/home/jovyan/tutorials" \
    --workdir="/home/jovyan" \
    "${image_name}-jupyter:${image_version}" \
    bash -c "start-notebook.sh --NotebookApp.token=''"

fi

popd > /dev/null

################################################################################################################################################################
