# Contributing

*This document is a work in progress.*

## Introduction

*TBC...*

## Guidelines

### Codebase

#### C++

Include order from specific to generic:

```cpp
#include <Library/Astrodynamics/Orbit.hpp>

#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Utilities.hpp>

#include <map>
#include <string>
```

References:

- https://stackoverflow.com/questions/2762568/c-c-include-file-order-best-practices
- https://blog.kowalczyk.info/article/qg/order-of-include-headers-in-cc.html

#### Python

*TBC...*

### Version Control

#### Rules

*TBC...*

#### Commit Messages

[How to Write a Git Commit Message](https://chris.beams.io/posts/git-commit/)

Use active form (`Do something`).

Prefix commit messages using the following tags:

- [feature]
- [fix]
- [misc]

Examples:

```txt
[feature] Implement high fidelity orbit propagator
```

```txt
[fix] Segmentation fault when fetching ephemeris data
```