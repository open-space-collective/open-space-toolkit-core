################################################################################################################################################################

# @project        Library ▸ Core
# @file           tools/testing/python/3.7/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM python:3.7

LABEL maintainer="lucas@loftorbital.com"

RUN pip install pytest>=5.0.1

COPY bindings/python/requirements.txt /requirements.txt

RUN pip install -r /requirements.txt

ENV LD_LIBRARY_PATH /usr/local/lib:/usr/local/lib/python3.7/site-packages:/library/core/lib
ENV PYTHONPATH /usr/local/lib/python3.7/site-packages:/library/core/lib

COPY bindings/python/tools/python/Library/Core /usr/local/lib/python3.7/site-packages/Library/Core

RUN mkdir -p /library \
 && mkdir -p /library/core

WORKDIR /library/core/test

CMD [ "pytest", "-sv" ]

################################################################################################################################################################
