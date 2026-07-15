---
sd_hide_title: true
---

# Open Space Toolkit ▸ Core

```{toctree}
:hidden:

Home <self>
```

```{toctree}
:hidden:
:caption: Documentation

tutorials/index
how-to/index
reference/index
explanation/index
```

<div align="center">

# Open Space Toolkit ▸ Core

**Common types, containers and utilities for the Open Space Toolkit.**

</div>

Open Space Toolkit Core provides the foundational building blocks used across
the Open Space Toolkit: fundamental {py:mod}`types <ostk.core.type>`,
{py:mod}`containers <ostk.core.container>`, a
{py:mod}`filesystem <ostk.core.filesystem>` abstraction, logging and error
handling. It is written in C++ and exposed to Python through pybind11 bindings.

## How the documentation is organised

This documentation follows the [Diátaxis](https://diataxis.fr/) framework. It is
split into four sections, each serving a different need. If you are not sure
where to start, the tutorials are the best entry point.

::::{grid} 1 1 2 2
:gutter: 3

:::{grid-item-card} {octicon}`mortar-board;1.5em;sd-mr-1` Tutorials
:link: tutorials/index
:link-type: doc

Learning-oriented lessons that take you by the hand through a series of steps
to build something with the toolkit. **Start here if you are new.**
:::

:::{grid-item-card} {octicon}`tools;1.5em;sd-mr-1` How-to guides
:link: how-to/index
:link-type: doc

Task-oriented, practical recipes that show how to solve a specific,
real-world problem.
:::

:::{grid-item-card} {octicon}`book;1.5em;sd-mr-1` Reference
:link: reference/index
:link-type: doc

Information-oriented, automatically generated descriptions of the Python and
C++ APIs.
:::

:::{grid-item-card} {octicon}`light-bulb;1.5em;sd-mr-1` Explanation
:link: explanation/index
:link-type: doc

Understanding-oriented discussion that clarifies and illuminates the design
and concepts behind the toolkit.
:::

::::

:::{admonition} About the Diátaxis framework
:class: seealso

The four sections above are not arbitrary. They correspond to the four distinct
documentation needs described by [Diátaxis](https://diataxis.fr/): *learning*,
*goals*, *information* and *understanding*. Keeping them separate makes the
documentation easier to write and much easier to use.
:::

## Installation

Install the Python package from [PyPI](https://pypi.org/project/open-space-toolkit-core/):

```bash
pip install open-space-toolkit-core
```

C++ binary packages are published on
[GitHub Releases](https://github.com/open-space-collective/open-space-toolkit-core/releases).
See the [how-to guides](how-to/index) for details.
