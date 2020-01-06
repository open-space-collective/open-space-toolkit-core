# Open Space Toolkit ▸ Core

[![Build Status](https://travis-ci.com/open-space-collective/open-space-toolkit-core.svg?branch=master)](https://travis-ci.com/open-space-collective/open-space-toolkit-core)
[![Code Coverage](https://codecov.io/gh/open-space-collective/open-space-toolkit-core/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/open-space-toolkit-core)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/open-space-toolkit-core)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-core.svg)](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-core)
[![PyPI version](https://badge.fury.io/py/open-space-toolkit-core.svg)](https://badge.fury.io/py/open-space-toolkit-core)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Common types, containers and utilities.

## Warning

*⚠ This component is under development.*

## Installation

### C++

The binary packages are hosted using [GitHub Releases](https://github.com/open-space-collective/open-space-toolkit-core/releases).

*Note: Don't forget to set the desired version number in the URLs!*

#### Debian / Ubuntu

```bash
# Download .deb packages

wget https://github.com/open-space-collective/open-space-toolkit-core/releases/download/0.3.0/open-space-toolkit-core-0.3.0-1.x86_64-runtime.deb
wget https://github.com/open-space-collective/open-space-toolkit-core/releases/download/0.3.0/open-space-toolkit-core-0.3.0-1.x86_64-devel.deb

# Install .deb packages

apt install -y open-space-toolkit-core-0.3.0-*.deb
```

#### Fedora / CentOS

```bash
# Download .rpm packages

wget https://github.com/open-space-collective/open-space-toolkit-core/releases/download/0.3.0/open-space-toolkit-core-0.3.0-1.x86_64-runtime.rpm
wget https://github.com/open-space-collective/open-space-toolkit-core/releases/download/0.3.0/open-space-toolkit-core-0.3.0-1.x86_64-devel.rpm

# Install .rpm packages

dnf install -y open-space-toolkit-core-0.3.0-*.rpm
```

### Python

The binary packages are hosted on [PyPI](https://pypi.org/project/open-space-toolkit-core/):

```bash
pip install open-space-toolkit-core
```

## Getting Started

Want to quickly get started? It's pretty simple.

Install [Docker](https://www.docker.com/) and try this:

```bash
docker run -it openspacecollective/open-space-toolkit-core-python
```

This will start an [iPython](https://ipython.org/) shell within a container where the OSTk Core component is already installed.

Once the shell is up and running, playing with it is easy:

```py
from ostk.core.filesystem import Directory # Directory class

Directory.root().is_empty() # True if the root directory is empty
```

*Tip: Use tab for auto-completion!*

## Structure

The **Core** library exhibits the following structure:

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

## Documentation

Documentation is available here:

- [C++](https://open-space-collective.github.io/open-space-toolkit-core)
- [Python](./bindings/python/docs)

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

| Name                | Version | License                | Link                                                                                               |
|---------------------|---------|------------------------|----------------------------------------------------------------------------------------------------|
| Boost               | 1.69.0  | Boost Software License | [boost.org](https://www.boost.org)                                                                 |
| RapidJSON           | master  | MIT                    | [rapidjson.org](http://rapidjson.org)                                                              |
| ordered-map         | master  | MIT                    | [github.com/Tessil/ordered-map](https://github.com/Tessil/ordered-map)                             |
| {fmt}               | master  | BSD-2-Clause           | [github.com/fmtlib/fmt](https://github.com/fmtlib/fmt)                                             |
| Rapidcsv            | master  | BSD-3-Clause           | [github.com/d99kris/rapidcsv](https://github.com/d99kris/rapidcsv)                                 |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

Apache License 2.0
