<!---
  Copyright (c) 2021 for information on the respective copyright owner
  see the NOTICE file and/or the repository https://github.com/boschglobal/automotive-bus-schema

  SPDX-License-Identifier: Apache-2.0
-->

# Automotive Bus Schema
(c) Robert Bosch GmbH under [Apache-2.0 license](https://www.apache.org/licenses/LICENSE-2.0)


## Introduction
This is a collection of schemas in the Google FlatBuffers IDL for describing automotive network communications within a virtualized simulation environment.
 Currently buffer representations of CAN, FlexRay, Ethernet and Encoded Signals at the level of a Communication Matrix definition are provided.

## Project structure
```
L- docs        Documentation
L- schemas     Schemas of the Standard

```


## Build Run and Use
### Compile
For compiling a FlatBuffers schema for your language please refer first to the official page
[for supported languages](https://google.github.io/flatbuffers/flatbuffers_support.html).

```bash
flatc [ GENERATOR OPTIONS ] [ -o PATH ] [ -I PATH ] FILES...
    [ -- FILES...]
```
Compiler options listed [here](https://google.github.io/flatbuffers/flatbuffers_guide_using_schema_compiler.html)

Note that for C language the [flatcc compiler](https://google.github.io/flatbuffers/flatbuffers_guide_use_c.html) is recommended.

### Usage
After compiling the output can be integrated in the simulation model code. Please refer to the [FlatBuffers Tutorial](https://google.github.io/flatbuffers/flatbuffers_guide_tutorial.html) for example usage of compiled code, e.g. how to read or write data structures defined in a schema.

## Dependencies

Schemas in this repository require [FlatBuffers](https://github.com/google/flatbuffers) v1.12.0 and [flatcc](https://github.com/dvidelabs/flatcc) v0.6.0 or later. Later versions may require testing.

## Contribute
Please refer to the [CONTRIBUTING.md](./CONTRIBUTING.md) for a quick read-up about what to consider if you want to contribute.


## License
Automotive Bus FlatBuffers Schema is open-sourced under the Apache-2.0 license. See the [LICENSE](./LICENSE) and [NOTICE](./NOTICE) for details.
