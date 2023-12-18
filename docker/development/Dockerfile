# Apache License 2.0

ARG BASE_IMAGE_VERSION="latest"

ENV TEST="test"

FROM openspacecollective/open-space-toolkit-base:${BASE_IMAGE_VERSION}

LABEL maintainer="lucas@loftorbital.com"

# Dependencies

## RapidJSON

ARG RAPIDJSON_VERSION="master"

RUN cd /tmp \
 && git clone --branch ${RAPIDJSON_VERSION} --depth 1 https://github.com/Tencent/rapidjson.git \
 && cd rapidjson \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/rapidjson

## yaml-cpp

ARG YAML_CPP_VERSION="0.7.0"

RUN cd /tmp \
 && git clone https://github.com/jbeder/yaml-cpp.git \
 && cd yaml-cpp \
 && git checkout tags/yaml-cpp-${YAML_CPP_VERSION} \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE -DYAML_BUILD_SHARED_LIBS=OFF -DYAML_CPP_BUILD_TESTS=OFF .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/yaml-cpp

## ordered-map

ARG ORDERED_MAP_VERSION="0.6.0"

RUN cd /tmp \
 && git clone --branch v${ORDERED_MAP_VERSION} --depth 1 https://github.com/Tessil/ordered-map.git \
 && cd ordered-map \
 && cp -r ./include/tsl /usr/local/include \
 && rm -rf /tmp/ordered-map

## {fmt}

ARG FMT_VERSION="5.2.0"

RUN cd /tmp \
 && git clone --branch ${FMT_VERSION} --depth 1 https://github.com/fmtlib/fmt.git \
 && cd fmt \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/fmt

## Rapidcsv

ARG RAPIDCSV_VERSION="6.11"

RUN cd /tmp \
 && git clone --branch v${RAPIDCSV_VERSION} --depth 1 https://github.com/d99kris/rapidcsv.git \
 && cd rapidcsv \
 && mkdir -p /usr/local/include/rapidcsv \
 && cp src/*.h /usr/local/include/rapidcsv/ \
 && rm -rf /tmp/rapidcsv

# Labels

ARG VERSION
ENV VERSION="${VERSION}"
LABEL VERSION="${VERSION}"

# Execution

CMD ["/bin/bash"]
