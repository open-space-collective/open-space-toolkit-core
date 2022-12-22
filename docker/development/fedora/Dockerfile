################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           docker/development/fedora/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

ARG BASE_IMAGE_VERSION=0.2.3
ARG BASE_IMAGE_SYSTEM=fedora

FROM openspacecollective/open-space-toolkit-base:${BASE_IMAGE_VERSION}-${BASE_IMAGE_SYSTEM}

LABEL maintainer="lucas@loftorbital.com"

# Dependencies

## RapidJSON [1.1.0]

RUN cd /tmp \
 && git clone https://github.com/miloyip/rapidjson.git \
 && cd rapidjson \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/rapidjson

## yaml-cpp [0.7.0]

RUN cd /tmp \
 && git clone https://github.com/jbeder/yaml-cpp.git \
 && cd yaml-cpp \
 && git checkout tags/yaml-cpp-0.7.0 \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE -DYAML_BUILD_SHARED_LIBS=OFF .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/yaml-cpp

## ordered-map [0.6.0]

RUN cd /tmp \
 && git clone --branch v0.6.0 --depth 1 https://github.com/Tessil/ordered-map.git \
 && cd ordered-map \
 && cp -r ./include/tsl /usr/local/include \
 && rm -rf /tmp/ordered-map

## {fmt} [5.2.0]

RUN cd /tmp \
 && git clone --branch 5.2.0 --depth 1 https://github.com/fmtlib/fmt.git \
 && cd fmt \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/fmt

## Rapidcsv [6.11]

RUN cd /tmp \
 && git clone --branch v6.11 --depth 1 https://github.com/d99kris/rapidcsv.git \
 && cd rapidcsv \
 && mkdir -p /usr/local/include/rapidcsv \
 && cp src/*.h /usr/local/include/rapidcsv/ \
 && rm -rf /tmp/rapidcsv

# Labels

ARG VERSION

ENV VERSION ${VERSION}

LABEL VERSION="${VERSION}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################
