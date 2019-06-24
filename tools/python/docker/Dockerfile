################################################################################################################################################################

# @project        Library ▸ Core
# @file           tools/python/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM jupyter/scipy-notebook:latest

LABEL maintainer="lucas@loftorbital.com"

USER root

RUN ln -s /opt/conda/include/python3.7m /opt/conda/include/python3.7

RUN jupyter labextension install @jupyterlab/plotly-extension

RUN python -m pip install --quiet numpy --upgrade \
 && python -m pip install --quiet plotly

COPY ./shortcuts-extension /home/jovyan/.jupyter/lab/user-settings/@jupyterlab/shortcuts-extension

RUN chown -R ${NB_UID}:${NB_UID} /home/jovyan/.jupyter

USER ${NB_UID}

RUN pip install LibraryCorePy

RUN mkdir -p /home/jovyan/.library

ENV JUPYTER_ENABLE_LAB yes

ENV LD_LIBRARY_PATH "/usr/local/lib:/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib"

ENV PYTHONPATH "/opt/conda/lib/python3.7/site-packages:/home/jovyan/lib"

################################################################################################################################################################
