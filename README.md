<!---
  Copyright (c) 2021 for information on the respective copyright owner
  see the NOTICE file and/or the repository https://github.com/boschglobal/automotive-bus-schema

  SPDX-License-Identifier: Apache-2.0
-->

# Automotive Bus Schema

[![CI](https://github.com/boschglobal/automotive-bus-schema/actions/workflows/ci.yaml/badge.svg)](https://github.com/boschglobal/automotive-bus-schema/actions/workflows/ci.yaml)
![GitHub](https://img.shields.io/github/license/boschglobal/automotive-bus-schema)

## Introduction

Automotive Bus Schema is a collection of schemas in the Google FlatBuffers IDL for describing automotive network communications within a virtualized simulation environment.

The repository currently provides buffer representations of CAN, FlexRay, Ethernet, and diagnostic communication at the level of a Communication Matrix definition.

### User Guide

* [Streams Example](doc/examples/streams.md) - How to use the Stream Interface Frame Schema with FlatBuffers.
* [FlatBuffers Tutorial](https://google.github.io/flatbuffers/flatbuffers_guide_tutorial.html)

### Project Structure

```text
automotive-bus-schema
├── doc                     <-- Project documentation.
├── docker                  <-- Containerized build toolchains.
├── examples                <-- Example projects.
├── schemas
│   ├── diagnostic          <-- Diagnostic schemas: ISO/TP, UDS, XiL etc.
│   ├── register            <-- Register based schemas: CAN, FlexRay, Ethernet.
│   └── stream              <-- Stream based schemas: PDU (CAN, FlexRay, Eth) and Frame (CAN).
├── templates               <-- Package templates.
└── Makefile                <-- Repo-level Makefile.
```

## Usage

After compiling the schemas, the generated output can be integrated into simulation model code. For more information about using FlatBuffers schemas, refer to the [FlatBuffers Tutorial](https://google.github.io/flatbuffers/flatbuffers_guide_tutorial.html).

This repository includes the following examples:

* [streams](doc/examples/streams.md) - How to use the Stream Interface Frame Schema with FlatBuffers.

## Build

The schemas can be compiled using the containerized build toolchain as follows:

```bash
# Clone the repo.
git clone https://github.com/boschglobal/automotive-bus-schema.git
cd automotive-bus-schema

# Optionally build the toolchains locally.
make builders

# Build and package the schemas.
make
make dist

# Remove temporary build artifacts.
make clean
```

### Toolchains

Automotive Bus Schema is built using containerized toolchains. Builder container images are published on `ghcr.io` and can be selected with the following variables:

```bash
export CONTAINER_REPO=ghcr.io
export CONTAINER_PREFIX=boschglobal/automotive-bus-schema-
export CONTAINER_TAG=main
export FLATC_BUILDER_IMAGE=${CONTAINER_REPO}/${CONTAINER_PREFIX}flatc-builder:${CONTAINER_TAG}
export PYTHON_BUILDER_IMAGE=${CONTAINER_REPO}/${CONTAINER_PREFIX}python-builder:${CONTAINER_TAG}
export GCC_BUILDER_IMAGE=${CONTAINER_REPO}/${CONTAINER_PREFIX}gcc-builder:${CONTAINER_TAG}
```

Alternatively, the builder images can be created locally:

```bash
make builders
```

The Dockerfiles used to generate the toolchains are available here:

* [Flatc/Flatcc builder](docker/flatc-builder/Dockerfile)
* [Python builder](docker/python-builder/Dockerfile)

For more information about compiling FlatBuffers schemas for your language, see the official [supported languages](https://google.github.io/flatbuffers/flatbuffers_support.html) and [schema compiler options](https://google.github.io/flatbuffers/flatbuffers_guide_using_schema_compiler.html) documentation.

> Note: For C language, the [flatcc compiler](https://google.github.io/flatbuffers/flatbuffers_guide_use_c.html) is recommended.

## Dependencies

Schemas in this repository require:

* [FlatBuffers](https://github.com/google/flatbuffers) v1.12.0 or v2.0.0 (or later).
* [flatcc](https://github.com/dvidelabs/flatcc) v0.6.0 (or later).

Later versions may require testing.

## Contribute

Please refer to the [CONTRIBUTING.md](./CONTRIBUTING.md) file.

## License

This project is open-sourced under the Apache-2.0 license.
See the [LICENSE](LICENSE) and [NOTICE](./NOTICE) files for details.
