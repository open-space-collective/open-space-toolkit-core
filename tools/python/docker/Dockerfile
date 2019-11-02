################################################################################################################################################################

# @project        Library ▸ Core
# @file           tools/python/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM jupyter/scipy-notebook:latest

LABEL maintainer="lucas@loftorbital.com"

USER root

# The following is to fix the "libstdc++.so.6: version `GLIBCXX_3.4.26' not found" error

RUN apt update \
 && apt-get install -y software-properties-common \
 && add-apt-repository ppa:ubuntu-toolchain-r/test \
 && apt-get update \
 && apt-get install -y gcc-9 \
 && apt-get upgrade -y libstdc++6 \
 && rm -rf /var/lib/apt/lists/* \
 && conda install -y libgcc=5.2.0 \
 && conda uninstall -y libgcc

RUN ln -s /opt/conda/include/python3.7m /opt/conda/include/python3.7

RUN jupyter labextension install @jupyterlab/plotly-extension

RUN python -m pip install --quiet numpy --upgrade \
 && python -m pip install --quiet plotly

COPY ./shortcuts-extension /home/jovyan/.jupyter/lab/user-settings/@jupyterlab/shortcuts-extension

RUN chown -R ${NB_UID}:${NB_UID} /home/jovyan/.jupyter

USER ${NB_UID}

RUN mkdir -p /home/jovyan/.library

ENV JUPYTER_ENABLE_LAB yes

ENV LD_LIBRARY_PATH "/usr/local/lib:/usr/lib/x86_64-linux-gnu:/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib"

ENV PYTHONPATH "/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib"

RUN pip install LibraryCorePy

################################################################################################################################################################
