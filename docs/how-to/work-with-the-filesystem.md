# How to work with the filesystem

The `filesystem` module provides portable `Path`, `File` and `Directory`
abstractions so you don't have to manipulate raw strings.

## Build a path

```python
from ostk.core.filesystem import Path

# From a string
path = Path.parse("/var/log/mission.log")

# Well-known locations
root = Path.root()        # "/"
here = Path.current()     # current working directory

print(path.to_string())
```

## Inspect a file

```python
from ostk.core.filesystem import File, Path

log = File.path(Path.parse("/var/log/mission.log"))

if log.exists():
    print(log.get_name())      # "mission.log"
    print(log.get_contents())  # file contents as a string
```

## Inspect a directory

```python
from ostk.core.filesystem import Directory, Path

directory = Directory.path(Path.parse("/etc"))

print(directory.exists())
print(directory.is_empty())
print(directory.get_name())
```

## Create and remove

```python
from ostk.core.filesystem import Directory, File, Path

new_dir = Directory.path(Path.parse("/tmp/ostk-demo"))

if not new_dir.exists():
    new_dir.create()

# ... use the directory ...

new_dir.remove()
```

```{seealso}
See the [filesystem reference](../reference/index) for the full list of methods
on `Path`, `File`, `Directory`, `SymbolicLink` and `PermissionSet`.
```
