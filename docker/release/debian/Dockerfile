################################################################################################################################################################

# @project        Library ▸ Core
# @file           docker/release/debian/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

ARG VERSION

FROM openspacecollective/library-core-development:${VERSION}-debian as cpp-builder

COPY . /app

RUN rm -rf /app/build \
 && mkdir /app/build

WORKDIR /app/build

RUN cmake .. \
 && make -j $(nproc) \
 && make install

################################################################################################################################################################

FROM debian:buster as cpp-release

ENV LD_LIBRARY_PATH /usr/local/lib

COPY --from=cpp-builder /usr/local/include/Library /usr/local/include/Library
COPY --from=cpp-builder /usr/local/lib/liblibrary-core.* /usr/local/lib/
COPY --from=cpp-builder /usr/local/share/Library /usr/local/share/Library
COPY --from=cpp-builder /usr/local/test/Library /usr/local/test/Library

ENTRYPOINT ["/usr/local/test/Library/Core/library-core.test"]

################################################################################################################################################################

FROM python:3.7-slim as python-builder

COPY --from=cpp-builder /app/build/bindings/python/dist /dist

RUN pip install /dist/*.whl

################################################################################################################################################################

FROM python:3.7-slim as python-release

LABEL maintainer="lucas@loftorbital.com"

COPY --from=python-builder /usr/local/lib/python3.7/site-packages/Library /usr/local/lib/python3.7/site-packages/Library

ENTRYPOINT ["python"]

################################################################################################################################################################
