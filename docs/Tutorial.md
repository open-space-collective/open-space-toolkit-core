Tutorial
========

Below are examples illustrating a few common use-cases.

[TOC]

# Setup {#Setup}

*To be completed...*

# Examples {#Examples}

## Load / Write JSON {#JSON}

[JSON](https://en.wikipedia.org/wiki/JSON) is a great format for configuring applications and for exchanging data over the internet:

Assuming an `input.json` file as follows:

```json
{
    "Key 1": "Hello World!"
}
```

the following code:

```cpp
// Setup JSON file

File jsonFile = File::Path(Path::String("/path/to/input.json")) ;

// Create object by loading JSON file

Object object = Object::Load(jsonFile) ;

// Get object value

String value = object["Key 1"].toString() ; // "Hello World!"

// Set object value

object["Key 2"] = Object::Integer(123) ;

// Save object

object.writeToFile(File::Path(Path::String("/path/to/output.json"))) ;
```

will return an `output.json` file as:

```json
{
    "Key 1": "Hello World!",
    "Key 2": 123
}
```