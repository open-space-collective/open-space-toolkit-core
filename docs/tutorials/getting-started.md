# Getting started

In this tutorial you will take your first steps with Open Space Toolkit Core.
By the end you will have imported the library, worked with its fundamental
types and containers, and inspected the filesystem. You do not need to know any
C++ — everything here uses the Python bindings.

This is a lesson, not a task list: follow along and run each snippet as you go.

## What you need

- Python 3.9 or later
- The package installed:

  ```bash
  pip install open-space-toolkit-core
  ```

Start an interactive session so you can experiment as you read:

```bash
python
```

## Step 1 — Import the toolkit

Everything lives under the `ostk.core` package. The three areas you will use
most are `type`, `container` and `filesystem`:

```python
from ostk.core.type import Integer, Real, String
from ostk.core.container import Array, Dictionary
from ostk.core.filesystem import Directory, File, Path
```

If those imports succeed, you are ready to go.

## Step 2 — Work with fundamental types

Open Space Toolkit wraps primitive values in rich types that carry extra
guarantees and behaviour. For example, `Real` and `Integer` model
possibly-undefined numeric values — useful in a domain where "no measurement"
is different from "zero":

```python
distance = Real(42.0)
print(distance.is_defined())   # True

undefined = Real.undefined()
print(undefined.is_defined())  # False
```

`String` behaves like you would expect, and interoperates with native Python
strings:

```python
name = String("Kepler")
print(name)                    # Kepler
```

## Step 3 — Use containers

`Array` is an ordered collection and `Dictionary` is a key/value store. They
map naturally onto Python's `list` and `dict`:

```python
values = Array.__call__([1, 2, 3])  # or construct from a Python list
print(len(values))

catalog = Dictionary.empty()
catalog["mission"] = String("Artemis")
print(catalog["mission"])
```

Containers know how to describe themselves — printing one gives you a readable
representation, which is handy while exploring in the REPL.

## Step 4 — Explore the filesystem

The `filesystem` module gives you portable `Path`, `File` and `Directory`
abstractions. Let's inspect the current working directory:

```python
current = Directory.path(Path.current())
print(current.exists())        # True
print(current.is_empty())      # Usually False
print(current.get_name())
```

You can build paths explicitly and point a `File` at them:

```python
path = Path.parse("/etc/hostname")
config = File.path(path)

if config.exists():
    print(config.get_contents())
```

## What you learned

You have:

- imported `ostk.core` and its `type`, `container` and `filesystem` modules;
- created fundamental types and checked whether they are defined;
- built and queried containers;
- inspected directories and files with the filesystem abstraction.

## Where to go next

```{seealso}
- Solve concrete problems with the [how-to guides](../how-to/index) — for
  example [loading and writing JSON](../how-to/load-write-json).
- Look up every class and method in the [reference](../reference/index).
- Understand *why* the toolkit models things this way in
  [explanation](../explanation/types-and-containers).
```
