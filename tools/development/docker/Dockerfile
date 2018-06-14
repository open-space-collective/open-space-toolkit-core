################################################################################################################################################################

# @project        Library/Core
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

FROM openspacecollective/library-base:latest

LABEL maintainer="lucas@loftorbital.com"

# Arguments

ARG version
ARG cpu_count=1

# Environment

ENV LD_LIBRARY_PATH /usr/local/lib:${LD_LIBRARY_PATH}

RUN alias ls='ls --color=auto' \
    && alias ll='ls -halF'

# Dependencies

## RapidJSON [1.1.0]

RUN mkdir /tmp/rapidjson \
 && cd /tmp/rapidjson \
 && git clone https://github.com/miloyip/rapidjson.git \
 && cd rapidjson \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make --silent -j ${cpu_count} \
 && make install \
 && rm -rf /tmp/rapidjson

## ordered-map

RUN mkdir /tmp/ordered-map \
 && cd /tmp/ordered-map \
 && git clone https://github.com/Tessil/ordered-map.git \
 && cd ordered-map \
 && cp -r ./tsl /usr/local/include \
 && rm -rf /tmp/ordered-map

# Labels

ENV version ${version}

LABEL version="${version}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################