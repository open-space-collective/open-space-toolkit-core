# How to load and write JSON

[JSON](https://en.wikipedia.org/wiki/JSON) is a convenient format for
configuring applications and exchanging data. Open Space Toolkit Core models
JSON documents with the `Object` container.

Assume an `input.json` file with the following contents:

```json
{
    "Key 1": "Hello World!"
}
```

## Load a JSON file

::::{tab-set}

:::{tab-item} Python
```python
from ostk.core.container import Object
from ostk.core.filesystem import File, Path

# Point a File at the JSON document
json_file = File.path(Path.parse("/path/to/input.json"))

# Load it as an Object
obj = Object.load(json_file, Object.Format.JSON)

# Read a value
print(obj["Key 1"].get_string())  # "Hello World!"
```
:::

:::{tab-item} C++
```cpp
#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

using ostk::core::container::Object;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;

// Point a File at the JSON document
File jsonFile = File::Path(Path::Parse("/path/to/input.json"));

// Load it as an Object
Object object = Object::Load(jsonFile);

// Read a value
String value = object["Key 1"].getString();  // "Hello World!"
```
:::

::::

## Parse JSON from a string

If the JSON is already in memory, parse it directly:

```python
from ostk.core.container import Object

obj = Object.parse('{"Key 1": "Hello World!"}', Object.Format.JSON)
print(obj["Key 1"].get_string())
```

## Build and serialise JSON

Construct an object from typed values and serialise it back to a JSON string:

```python
from ostk.core.container import Dictionary, Object
from ostk.core.filesystem import File, Path

contents = Dictionary.empty()
contents.add_value_for_key(Object.string("Hello World!"), "Key 1")
contents.add_value_for_key(Object.integer(123), "Key 2")

obj = Object.dictionary(contents)

# Serialise to a JSON string
json_string = obj.to_string(Object.Format.JSON)

# Write it to disk
with open("/path/to/output.json", "w") as handle:
    handle.write(json_string)
```

This produces:

```json
{
    "Key 1": "Hello World!",
    "Key 2": 123
}
```

```{tip}
`Object` also supports YAML via `Object.Format.YAML` for both parsing and
serialisation.
```
