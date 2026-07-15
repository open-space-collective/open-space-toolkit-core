# How to install the toolkit

## Python

Install the package from [PyPI](https://pypi.org/project/open-space-toolkit-core/):

```bash
pip install open-space-toolkit-core
```

Verify the installation:

```bash
python -c "from ostk.core.filesystem import Directory; print(Directory.root().is_empty())"
```

## C++

Binary packages are published on
[GitHub Releases](https://github.com/open-space-collective/open-space-toolkit-core/releases):

- Runtime libraries: `open-space-toolkit-core-X.Y.Z-1.x86_64-runtime`
- C++ headers: `open-space-toolkit-core-X.Y.Z-1.x86_64-devel`
- Python bindings: `open-space-toolkit-core-X.Y.Z-1.x86_64-python`

### Debian / Ubuntu

After downloading the relevant `.deb` packages, install them with:

```bash
apt install ./open-space-toolkit-core-*.deb
```

## Run without installing (Docker)

If [Docker](https://www.docker.com/) is available, you can try the toolkit
without installing anything locally.

Start an IPython shell with the toolkit already available:

```bash
docker run -it openspacecollective/open-space-toolkit-core-development python3.11 -m IPython
```

Or launch a JupyterLab server:

```bash
docker run --publish=8888:8888 openspacecollective/open-space-toolkit-core-jupyter
```

Then open <http://localhost:8888/lab>.

```{seealso}
To build from source, see the
[contributing guide](https://github.com/open-space-collective/open-space-toolkit-core/blob/main/CONTRIBUTING.md).
```
