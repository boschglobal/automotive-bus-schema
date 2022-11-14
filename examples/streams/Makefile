# Copyright (C) 2022 Robert Bosch GmbH

GCC_BUILDER_IMAGE ?= gcc-builder:latest

ifneq ($(CI), true)
	DOCKER_BUILDER_CMD := docker run -it --rm \
		--volume $$(pwd)/../..:/tmp/repo \
		--volume ~/.ccache:/root/.ccache \
		--workdir /tmp/repo/examples/streams \
		$(GCC_BUILDER_IMAGE)
endif

.PHONY: build  clean do-build run

default: build

build:
	@${DOCKER_BUILDER_CMD} $(MAKE) do-build

do-build:
# Build from scratch if no build dir.
	@if [ ! -d "build" ]; then \
		mkdir -p build; \
		cd build; \
		cmake .. ; \
	fi
# Build incremental.
	cd build; make
	cd build; make install
	@echo ""
	@echo "Sandbox files: - $$(pwd)/build/_out"
	@echo "--------------"
	@find build/_out/ -type f -name '*' -exec ls -sh --color=auto {} \;

run:
	@build/_out/bin/frames

clean:
	rm -rf build