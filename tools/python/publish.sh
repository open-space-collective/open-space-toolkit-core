#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/python/publish.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Package

pushd ${script_directory} >> /dev/null

source ../.env

python3 -m pip install twine

# twine upload -r pypitest dist/*
python3 -m twine upload --repository-url https://test.pypi.org/legacy/ dist/*

popd >> /dev/null

################################################################################################################################################################