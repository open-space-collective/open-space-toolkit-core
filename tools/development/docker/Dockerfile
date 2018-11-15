################################################################################################################################################################

# @project        Library/Core
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM openspacecollective/library-base:0.1.5

LABEL maintainer="lucas@loftorbital.com"

# Arguments

ARG cpu_count=1

# Dependencies

## RapidJSON [1.1.0]

RUN pushd /tmp > /dev/null \
 && git clone https://github.com/miloyip/rapidjson.git \
 && cd rapidjson \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make --silent -j ${cpu_count} \
 && make install \
 && rm -rf /tmp/rapidjson \
 && popd > /dev/null

## ordered-map [0.6.0]

RUN pushd /tmp > /dev/null \
 && git clone --branch v0.6.0 --depth 1 https://github.com/Tessil/ordered-map.git \
 && cd ordered-map \
 && cp -r ./include/tsl /usr/local/include \
 && rm -rf /tmp/ordered-map \
 && popd > /dev/null

## {fmt} [5.2.0]

RUN pushd /tmp > /dev/null \
 && git clone --branch 5.2.0 --depth 1 https://github.com/fmtlib/fmt.git \
 && cd fmt \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE .. \
 && make --silent -j ${cpu_count} \
 && make install \
 && rm -rf /tmp/fmt \
 && popd > /dev/null

## Rapidcsv [master]

RUN pushd /tmp > /dev/null \
 && git clone https://github.com/d99kris/rapidcsv.git \
 && cd rapidcsv \
 && mkdir -p /usr/local/include/rapidcsv \
 && cp src/*.h /usr/local/include/rapidcsv/ \
 && rm -rf /tmp/rapidcsv \
 && popd > /dev/null

# Labels

ARG version

ENV version ${version}

LABEL version="${version}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################