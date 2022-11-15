<!---
  Copyright (c) 2022 for information on the respective copyright owner
  see the NOTICE file and/or the repository https://github.com/boschglobal/automotive-bus-schema

  SPDX-License-Identifier: Apache-2.0
-->


# Example: Stream Interface - Frame Schema (with FlatBuffers)

## Build the Toolchain Container Images

> Note: This may take some time.


```bash
$ git clone https://github.com/boschglobal/automotive-bus-schema.git
$ cd automotive-bus-schema
$ make builders
...
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
python-builder      latest              a5ef73ea66dc        16 minutes ago      858MB
flatc-builder       latest              f4bb83e2c0c9        18 minutes ago      324MB
gcc-builder         latest              7f15adf64b0a        5 seconds ago       620MB
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
$ cd examples/streams
$ make
...
Sandbox files: - /tmp/repo/examples/streams/build/_out
--------------
312K build/_out/bin/frames

# Run the target executable.
$ make run
Process stream (length = 136)
Sending Node UID is: 49
CAN Frame:
  frame_id     = 42
  payload      = 66 6f 6f
  length       = 3
  frame_type   = 0
  bus_id       = 1
  node_id      = 0
  interface_id = 0
CAN Frame:
  frame_id     = 24
  payload      = 62 61 72
  length       = 3
  frame_type   = 0
  bus_id       = 1
  node_id      = 0
  interface_id = 0
```
