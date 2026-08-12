# About Open Space Toolkit Core

## What it is

Open Space Toolkit Core is the foundation of the
[Open Space Toolkit](https://github.com/open-space-collective/open-space-toolkit),
a collection of open-source libraries for space engineering and mission
analysis. Core provides the common vocabulary that every other component builds
on: fundamental types, containers, a filesystem abstraction, logging and error
handling.

It deliberately contains no domain-specific astrodynamics — that lives in the
higher-level toolkit components (mathematics, physics, astrodynamics, …). Core's
job is to make those components consistent, portable and pleasant to use.

## Where it sits

```{mermaid}
graph TD
    Core["Open Space Toolkit ▸ Core<br/><i>types, containers, filesystem</i>"]
    Math["Mathematics"]
    Physics["Physics"]
    Astro["Astrodynamics"]

    Core --> Math
    Math --> Physics
    Physics --> Astro
```

Every component above depends, directly or transitively, on Core. A change to a
type or container here ripples across the whole toolkit, which is why Core
values stability and clarity over breadth.

## Design principles

**One implementation, two languages.** The library is written in C++ for
performance and exposed to Python through
[pybind11](https://pybind11.readthedocs.io/) bindings. The Python API mirrors
the C++ API closely, so knowledge transfers between the two. This is also why
the [reference](../reference/index) is generated automatically from both the
C++ headers and the compiled Python module — the two never drift apart.

**Explicit over implicit.** Values can be *defined* or *undefined* rather than
relying on sentinels like `NaN` or `null`. This makes "no value" a first-class,
checkable state, which matters when propagating measurements and computations.

**Portability.** Filesystem access, string handling and containers are wrapped
so that code behaves the same across platforms.

```{seealso}
For the concrete reasoning behind the type and container abstractions, see
[Types and containers](types-and-containers).
```
