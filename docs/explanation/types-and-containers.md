# Types and containers

Newcomers often ask why Open Space Toolkit Core wraps ordinary values —
integers, reals, strings, lists — in its own types instead of using the native
language primitives. This page explains the reasoning.

## Rich types

The `type` module provides `Integer`, `Real`, `String` and `Sign`. On the
surface they resemble their built-in counterparts, but they add semantics that
matter in an engineering context.

The most important addition is the notion of being **defined** or
**undefined**. In numerical space computations, the absence of a value is
common and meaningful: a measurement may be missing, a computation may not have
converged, a quantity may be out of range. Representing that with `NaN`,
`None`, `-1` or `0` is error-prone — those sentinels can silently propagate and
be mistaken for real data.

Instead, every value can be explicitly undefined and checked:

```python
from ostk.core.type import Real

r = Real.undefined()
if r.is_defined():
    use(r)
```

Because the C++ and Python types share this behaviour, the same guarantees hold
whether you are writing performance-critical C++ or exploratory Python.

## Containers

The `container` module provides `Array`, `Dictionary` and `Object`.

- **`Array`** is an ordered, homogeneous-friendly collection — the toolkit's
  equivalent of a `std::vector` / Python `list`.
- **`Dictionary`** is an ordered key/value map.
- **`Object`** is a self-describing, dynamically-typed value used to represent
  structured data such as JSON and YAML. An `Object` knows its own type
  (`Boolean`, `Integer`, `Real`, `String`, array or dictionary) and can be
  queried and serialised accordingly.

`Object` is what makes configuration and data-exchange ergonomic: you load a
document once and then interrogate it with type-safe accessors like
`get_string()` or `get_integer()`, rather than juggling raw parse trees. See
[How to load and write JSON](../how-to/load-write-json) for this in practice.

## Why mirror C++ and Python

The library is implemented once in C++ and exposed to Python through pybind11.
Keeping the container and type semantics identical across both languages means:

- documentation, examples and mental models transfer directly;
- the [API reference](../reference/index) can be generated from a single source
  of truth on each side (Doxygen for C++, module introspection for Python)
  without the two descriptions drifting apart;
- performance-sensitive code can drop to C++ without changing how data is
  modelled.

This consistency is a deliberate design goal, not an accident of binding
generation.
