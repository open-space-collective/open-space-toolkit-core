# Apache License 2.0

ARG JUPYTER_NOTEBOOK_IMAGE_REPOSITORY="jupyter/scipy-notebook:latest"

FROM ${JUPYTER_NOTEBOOK_IMAGE_REPOSITORY}

LABEL maintainer="lucas@loftorbital.com"

USER root

# Install extensions

RUN pip install "plotly" "numpy" "ipywidgets>=7.6"

RUN jupyter labextension install --no-build \
        @jupyterlab/shortcuts-extension

COPY ./shortcuts-extension /home/jovyan/.jupyter/lab/user-settings/@jupyterlab/shortcuts-extension

RUN chown -R ${NB_UID}:${NB_UID} /home/jovyan/.jupyter

USER ${NB_UID}

ENV JUPYTER_ENABLE_LAB="yes"
ENV LD_LIBRARY_PATH="/usr/local/lib:/usr/lib/x86_64-linux-gnu:/opt/conda/lib/python3.8/site-packages:/home/jovyan/lib:/opt/conda/lib"
ENV PYTHONPATH="/opt/conda/lib/python3.8/site-packages:/home/jovyan/lib"

RUN pip install open-space-toolkit-core
