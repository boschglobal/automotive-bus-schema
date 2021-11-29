<!---
  Copyright (c) 2021 for information on the respective copyright owner
  see the NOTICE file and/or the repository https://github.com/boschglobal/automotive-bus-schema

  SPDX-License-Identifier: Apache-2.0
-->


# Example: CMake Project with Signal Schema and MsgPack

## Build the Toolchain Container Image

```bash
$ git clone https://github.com/boschglobal/automotive-bus-schema.git
$ cd automotive-bus-schema
$ make builders
...
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
python-builder      latest              a5ef73ea66dc        16 minutes ago      858MB
flatc-builder       latest              f4bb83e2c0c9        18 minutes ago      324MB
```


## Build and package the schemas

```bash
$ make
...
$ make dist
Distribution package files:
--------------------------
204K /vagrant/git/oss/automotive-bus-schema/dist/automotive-bus-schema.tar.gz
36K /vagrant/git/oss/automotive-bus-schema/dist/python/dist/automotive_bus_schema-devel-py3-none-any.whl
12K /vagrant/git/oss/automotive-bus-schema/dist/python/dist/automotive-bus-schema-devel.tar.gz
```


## Build and run the example

```bash
$ cd examples/cmake
$ make
[ 20%] Building C object CMakeFiles/example.dir/example.c.o
[ 40%] Building C object CMakeFiles/example.dir/tmp/repo/dist/automotive-bus-schema/flatbuffers/c/automotive_bus_schema/flatcc/src/builder.c.o
[ 60%] Building C object CMakeFiles/example.dir/tmp/repo/dist/automotive-bus-schema/flatbuffers/c/automotive_bus_schema/flatcc/src/emitter.c.o
[ 80%] Building C object CMakeFiles/example.dir/tmp/repo/dist/automotive-bus-schema/flatbuffers/c/automotive_bus_schema/flatcc/src/refmap.c.o
[100%] Linking C executable example
make[3]: warning:  Clock skew detected.  Your build may be incomplete.
make[3]: Leaving directory '/tmp/repo/examples/cmake/build'
[100%] Built target example

# Run the target executable.
$ ./build/example
FBS Buffer:
----------
4c 00 00 00 08 00 00 00 53 49 43 48 c6 ff ff ff
5f 0b 00 00 08 00 00 00 01 00 00 00 dc ff ff ff
04 00 00 00 17 00 00 00 92 92 2a 18 92 cb 40 45
00 00 00 00 00 00 cb 40 38 00 00 00 00 00 00 00
06 00 08 00 04 00 0a 00 0d 00 04 00 0c 00 08 00
```
