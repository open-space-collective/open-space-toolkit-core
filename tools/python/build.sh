#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/python/build.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd ${script_directory} >> /dev/null

# Setup environment

source ../.env

# Build package

python3 -m pip install --user --upgrade setuptools wheel

rm -rf ./LibraryCorePy

mkdir -p ./LibraryCorePy

cp /app/share/python/tools/python/__init__.py ./LibraryCorePy/
cp /app/lib/LibraryCorePy.so ./LibraryCorePy/
cp /app/lib/liblibrary-core.so.0 ./LibraryCorePy/

python3 setup.py bdist_wheel

popd >> /dev/null

################################################################################################################################################################