#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/docker/setup.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

# Parameters

project_name="library-core"

# Setup

## Version

version=$(git describe --tags 2>/dev/null || true)

if [[ -z $version ]]; then
    version=$(head -n 4096 /dev/urandom | shasum | cut -d' ' -f1)
fi

## Platform

cpu_count=1

if [ "$(uname)" == "Darwin" ]; then
    cpu_count=$(sysctl -n hw.ncpu)
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    cpu_count=$(cat /proc/cpuinfo | grep '^processor.*:' | wc -l)
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    echo "32 bits Windows NT platform not supported"
    exit 1
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    echo "64 bits Windows NT platform not supported"
    exit 1
fi

## Image

image_name="${project_name}"

project_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"/../..

################################################################################################################################################################