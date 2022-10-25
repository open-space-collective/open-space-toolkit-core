# Open Space Toolkit ▸ Core

[![Build and Test](https://github.com/open-space-collective/open-space-toolkit-core/actions/workflows/build-test.yml/badge.svg?branch=main)](https://github.com/open-space-collective/open-space-toolkit-core/actions/workflows/build-test.yml)
[![Code Coverage](https://codecov.io/gh/open-space-collective/open-space-toolkit-core/branch/main/graph/badge.svg)](https://codecov.io/gh/open-space-collective/open-space-toolkit-core)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/open-space-toolkit-core)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-core.svg)](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-core)
[![PyPI version](https://badge.fury.io/py/open-space-toolkit-core.svg)](https://badge.fury.io/py/open-space-toolkit-core)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Common types, containers and utilities.

## Getting Started

Want to get started? This is the simplest and quickest way:

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/open-space-collective/open-space-toolkit/main?urlpath=lab/tree/notebooks)

*Nothing to download or install! This will automatically start a [JupyterLab](https://jupyterlab.readthedocs.io/en/stable/) environment in your browser with Open Space Toolkit libraries and example notebooks ready to use.*

### Alternatives

#### Docker Images

[Docker](https://www.docker.com/) must be installed on your system.

##### iPython

The following command will start an [iPython](https://ipython.org/) shell within a container where the OSTk components are already installed:

```bash
docker run -it openspacecollective/open-space-toolkit-core-python
```

Once the shell is up and running, playing with it is easy:

```py
from ostk.core.filesystem import Directory # Directory class

Directory.root().is_empty() # True if the root directory is empty
```

*Tip: Use tab for auto-completion!*

##### JupyterLab

The following command will start a [JupyterLab](https://jupyterlab.readthedocs.io/en/stable/) server within a container where the OSTk components are already installed:

```bash
docker run --publish=8888:8888 openspacecollective/open-space-toolkit-core-jupyter
```

Once the container is running, access [http://localhost:8888/lab](http://localhost:8888/lab) and create a Python 3 Notebook.

## Installation

### C++

The binary packages are hosted using [GitHub Releases](https://github.com/open-space-collective/open-space-toolkit-core/releases):

- Runtime libraries: `open-space-toolkit-core-X.Y.Z-1.x86_64-runtime`
- C++ headers: `open-space-toolkit-core-X.Y.Z-1.x86_64-devel`
- Python bindings: `open-space-toolkit-core-X.Y.Z-1.x86_64-python`

#### Debian / Ubuntu

After downloading the relevant `.deb` binary packages, install:

```bash
apt install open-space-toolkit-core-*.deb
```

#### Fedora / CentOS

After downloading the relevant `.rpm` binary packages, install:

```bash
dnf install open-space-toolkit-core-*.rpm
```

### Python

Install from [PyPI](https://pypi.org/project/open-space-toolkit-core/):

```bash
pip install open-space-toolkit-core
```

## Documentation

Documentation is available here:

- [C++](https://open-space-collective.github.io/open-space-toolkit-core)
- [Python](./bindings/python/docs)

<details>
<summary>Structure</summary>
<p>
The library exhibits the following structure:

```txt
├── Types
│   ├── Integer
│   ├── Real
│   ├── String
│   ├── Byte
│   ├── Byte Array
│   ├── Index
│   ├── Size
│   ├── Sign
│   ├── Unique
│   ├── Shared
│   └── Weak
├── Containers
│   ├── Array
│   ├── List
│   ├── Map
│   ├── Ordered Map
│   ├── Object
│   ├── Dictionary
│   ├── Pair
│   ├── Triple
│   ├── Tuple
│   ├── Table
│   ├── Queue
│   ├── Stack
│   ├── Graph
│   └── Tree
├── File System
│   ├── Path
│   ├── File
│   ├── Directory
│   ├── Symbolic Link
│   └── Permission
├── System
│   ├── User
│   ├── Group
│   ├── CPU
│   ├── Memory
│   ├── Disk
│   └── Process
├── Logger
├── Error
│   ├── Exception
│   ├── Runtime Error
│   └── Runtime
│       ├── Undefined
│       ├── Wrong
│       └── To Be Implemented
└── Utilities
    ├── Iterators
    └── Version
```
</p>
</details>

## Tutorials

Tutorials are available here:

- [C++](./tutorials/cpp)
- [Python](./tutorials/python)

## Setup

### Development Environment

Using [Docker](https://www.docker.com) for development is recommended, to simplify the installation of the necessary build tools and dependencies.
Instructions on how to install Docker are available [here](https://docs.docker.com/install/).

To start the development environment:

```bash
make start-development
```

This will:

1. Build the `openspacecollective/open-space-toolkit-core-development` Docker image.
2. Create a development environment container with local source files and helper scripts mounted.
3. Start a `bash` shell from the `./build` working directory.

If installing Docker is not an option, you can manually install the development tools (GCC, CMake) and all required dependencies, by following a procedure similar to the one described in the [Development Dockerfile](./docker/development/Dockerfile).

### Build

From the `./build` directory:

```bash
cmake ..
make
```

*Tip: `helpers/build.sh` simplifies building from within the development environment.*

### Test

To start a container to build and run the tests:

```bash
make test
```

Or to run them manually:

```bash
./bin/open-space-toolkit-core.test
```

*Tip: `helpers/test.sh` simplifies running tests from within the development environment.*

## Dependencies

| Name        | Version | License                | Link                                                                   |
| ----------- | ------- | ---------------------- | ---------------------------------------------------------------------- |
| Pybind11    | 2.6.1   | BSD-3-Clause           | [github.com/pybind/pybind11](https://github.com/pybind/pybind11)       |
| RapidJSON   | master  | MIT                    | [rapidjson.org](http://rapidjson.org)                                  |
| ordered-map | master  | MIT                    | [github.com/Tessil/ordered-map](https://github.com/Tessil/ordered-map) |
| {fmt}       | master  | BSD-2-Clause           | [github.com/fmtlib/fmt](https://github.com/fmtlib/fmt)                 |
| Rapidcsv    | master  | BSD-3-Clause           | [github.com/d99kris/rapidcsv](https://github.com/d99kris/rapidcsv)     |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

[![Loft Orbital](https://github.com/open-space-collective/open-space-toolkit/blob/main/assets/thanks/loft_orbital.png)](https://www.loftorbital.com/)

## License

Apache License 2.0
