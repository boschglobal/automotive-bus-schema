#***************************************************************************
# Copyright (c) 2021 for information on the respective copyright owner
# see the NOTICE file and/or the following repository:
#     https://github.com/boschglobal/automotive-bus-schema
#
# SPDX-License-Identifier: Apache-2.0
#***************************************************************************


###############
## Builder Images
FLATC_BUILDER_IMAGE ?= flatc-builder:latest


default: build_docker

all: build
	cd build; make

build:
	mkdir build;
	cd build; cmake ..

build_docker:
	@docker run -it --rm \
		--volume $$(pwd)/../..:/tmp/repo \
		--workdir /tmp/repo/examples/cmake \
		$(FLATC_BUILDER_IMAGE) \
		/bin/bash -c "make all"

clean:
	rm -rf build

cleanall: clean


.PHONY: default all clean cleanall
