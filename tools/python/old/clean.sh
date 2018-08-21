#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/python/clean.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd ${script_directory} >> /dev/null

# Setup environment

source ../.env

# Delete files

rm -rf build dist LibraryCorePy LibraryCorePy.egg-info

popd >> /dev/null

################################################################################################################################################################