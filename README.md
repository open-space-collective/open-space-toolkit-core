Library ▸ Core
==============

Fundamental types, containers and utilities.

[![Build Status](https://travis-ci.com/open-space-collective/library-core.svg?branch=master)](https://travis-ci.com/open-space-collective/library-core)
[![Code Coverage](https://codecov.io/gh/open-space-collective/library-core/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/library-core)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/library-core)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Flibrary-core.svg)](https://badge.fury.io/gh/open-space-collective%2Flibrary-core)
[![PyPI version](https://badge.fury.io/py/LibraryCorePy.svg)](https://badge.fury.io/py/LibraryCorePy)

## Warning

Library **name** and **license** are yet to be defined.

Please check the following projects:

- [Naming Project](https://github.com/orgs/open-space-collective/projects/1)
- [Licensing Project](https://github.com/orgs/open-space-collective/projects/2)

*⚠ This library is still under heavy development. Do not use!*

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

The documentation can be found here:

- [C++](https://open-space-collective.github.io/library-core)
- [Python](./bindings/python/docs)

## Tutorials

Various tutorials are available here:

- [C++](./tutorials/cpp)
- [Python](./tutorials/python)

## Setup

### Development

Using [Docker](https://www.docker.com) is recommended, as the development tools and dependencies setup is described in the provided [Dockerfile](./tools/development/docker/Dockerfile).

Instructions on how to install Docker can be found [here](https://docs.docker.com/install/).

To start a development environment:

```bash
./tools/development/start.sh
```

This will also build the `openspacecollective/library-core:latest` Docker image, if not already.

If installing Docker is not an option, please manually install the development tools (GCC, CMake) and all required dependencies.
The procedure should be similar to the one described in the [Dockerfile](./tools/development/docker/Dockerfile).

### Build

From the development environment:

```bash
./build.sh
```

Manually:

```bash
mkdir -p build
cd build
cmake ..
make
```

### Test

From the development environment:

```bash
./test.sh
```

Manually:

```bash
./bin/library-core.test
```

## Dependencies

The **Core** library internally uses the following dependencies:

| Name                | Version | License                | Link                                                                                               |
|---------------------|---------|------------------------|----------------------------------------------------------------------------------------------------|
| Boost               | 1.67.0  | Boost Software License | [boost.org](https://www.boost.org)                                                                 |
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

*To be defined...*