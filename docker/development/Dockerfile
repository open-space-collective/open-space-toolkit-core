# Apache License 2.0

ARG BASE_IMAGE_VERSION="latest"

# General purpose development image (root user)

FROM openspacecollective/open-space-toolkit-base:${BASE_IMAGE_VERSION} as root-user

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

# Development image for humans (non-root user)

FROM root-user as non-root-user

# Install dev utilities
RUN apt-get update \
 && apt-get install -y zsh sudo \
 && rm -rf /var/lib/apt/lists/*

# Create non-root user and group

ARG USERNAME="developer"
ARG USER_UID="1000"
ARG USER_GID=${USER_UID}
RUN groupadd --gid ${USER_GID} ${USERNAME} || true \
 && adduser --uid ${USER_UID} --gid ${USER_GID} ${USERNAME} \
 && echo "${USERNAME} ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers.d/${USERNAME}

# Use non-root user

USER ${USERNAME}

# Install shell utilities

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" \
 && git clone https://github.com/bhilburn/powerlevel9k.git /home/${USERNAME}/.oh-my-zsh/custom/themes/powerlevel9k \
 && git clone https://github.com/zsh-users/zsh-autosuggestions /home/${USERNAME}/.oh-my-zsh/custom/plugins/zsh-autosuggestions \
 && git clone https://github.com/zsh-users/zsh-syntax-highlighting.git /home/${USERNAME}/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting \
 && mkdir -p /home/${USERNAME}/.vscode-server/extensions /home/${USERNAME}/.vscode-server-insiders/extensions

## Configure environment

ENV PATH="/home/${USERNAME}/.local/bin:${PATH}"

# Entrypoint

CMD [ "/bin/bash" ]
