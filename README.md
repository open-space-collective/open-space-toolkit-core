Library :: Core
===============

Fundamental types, containers and utilities.

[![Build Status](https://travis-ci.com/open-space-collective/library-core.svg?branch=master)](https://travis-ci.com/open-space-collective/library-core)
[![Code Coverage](https://codecov.io/gh/open-space-collective/library-core/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/library-core)
[![Documentation](https://readthedocs.org/projects/docs/badge/?version=latest)](https://open-space-collective.github.io/library-core)

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
├── Program
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

The documentation can be found [here](https://open-space-collective.github.io/library-core).

## Setup

### Development

Using [Docker](https://www.docker.com) is recommended, as the development tools and dependencies setup is described in the provided [Dockerfile](./tools/development/docker/Dockerfile).

Instructions to install Docker can be found [here](https://docs.docker.com/install/).

Start the development environment:

```bash
./tools/development/start.sh
```

This will also build the `openspacecollective/library-core:latest` Docker image, if not present already.

If installing Docker is not an option, please manually install the development tools (GCC, CMake) and the dependencies.
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

| Name        | Version | License                | Link                                                                   |
|-------------|---------|------------------------|------------------------------------------------------------------------|
| Boost       | 1.67.0  | Boost Software License | [boost.org](https://www.boost.org)                                     |
| RapidJSON   | master  | MIT                    | [rapidjson.org](http://rapidjson.org)                                  |
| ordered-map | master  | MIT                    | [github.com/Tessil/ordered-map](https://github.com/Tessil/ordered-map) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

*To be defined...*