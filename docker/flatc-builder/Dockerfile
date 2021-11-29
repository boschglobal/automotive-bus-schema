FROM debian:bullseye-slim AS builder


# =========================
# Builder image
# =========================
# Partly derived from the following Dockerfile :
#   https://github.com/neomantra/docker-flatbuffers/blob/master/Dockerfile


# Setup basic GCC and CMAKE toolchains
# ====================================
RUN apt-get -y update; \
    apt-get -y upgrade; \
    apt-get -y install --no-install-recommends \
        binutils \
        build-essential \
        ca-certificates \
        cmake \
        extra-cmake-modules \
        curl \
        g++ \
        git \
        less \
        make \
    && \
    apt-get clean; \
    rm -rf /var/lib/apt/lists/*


# FlatBuffer Build
# ================
# https://github.com/google/flatbuffers/archive/refs/tags/v2.0.0.tar.gz
ARG FLATBUFFERS_ARCHIVE_BASE_URL="https://github.com/google/flatbuffers/archive/refs/tags"
ARG FLATBUFFERS_ARCHIVE_TAG="v2.0.0"
ARG FLATBUFFERS_BUILD_TYPE="Release"

RUN curl -fSL "${FLATBUFFERS_ARCHIVE_BASE_URL}/${FLATBUFFERS_ARCHIVE_TAG}.tar.gz" -o flatbuffers.tar.gz \
    && tar xzf flatbuffers.tar.gz \
    && cd flatbuffers-* \
    && cmake -G "Unix Makefiles"  \
        -DFLATBUFFERS_CXX_FLAGS="-Wno-error" \
        -DFLATBUFFERS_BUILD_TESTS=OFF \
        -DCMAKE_BUILD_TYPE=${FLATBUFFERS_BUILD_TYPE} \
        . \
    && make \
    && make install \
    && cp src/idl_parser.cpp src/idl_gen_text.cpp /usr/local/include/flatbuffers


# Flatcc Build
# ============
# https://github.com/dvidelabs/flatcc/archive/refs/tags/v0.6.0.tar.gz
ARG FLATCC_ARCHIVE_BASE_URL="https://github.com/dvidelabs/flatcc/archive/refs/tags"
ARG FLATCC_ARCHIVE_TAG="v0.6.0"

RUN curl -fSL "${FLATCC_ARCHIVE_BASE_URL}/${FLATCC_ARCHIVE_TAG}.tar.gz" -o flatcc.tar.gz \
    && tar xzf flatcc.tar.gz \
    && mv flatcc-* flatcc \
    && cd flatcc \
    && ./scripts/initbuild.sh make \
    && ./scripts/build.sh


# =========================
# Construct the final image
# =========================
FROM debian:bullseye-slim


# Setup basic tools
# =================
RUN apt-get -y update; \
    apt-get -y upgrade; \
    apt-get -y install --no-install-recommends \
        build-essential \
        curl \
        cmake \
        gcc \
        git \
        libmsgpack-dev \
        make \
        zip \
    && \
    apt-get clean; \
    rm -rf /var/lib/apt/lists/*


# Flatbuffers (flatc)
# ===================
COPY --from=builder /usr/local/bin/flatc /usr/local/bin/flatc
COPY --from=builder /usr/local/include/flatbuffers /usr/local/include/flatbuffers
COPY --from=builder /usr/local/lib/libflatbuffers.a /usr/local/lib/libflatbuffers.a
COPY --from=builder /usr/local/lib/cmake/flatbuffers /usr/local/lib/cmake/flatbuffers


# Flatcc (flatcc)
# ===============
COPY --from=builder /flatcc/bin/flatcc /usr/local/bin/flatcc
COPY --from=builder /flatcc/include/flatcc /usr/local/include/flatcc
COPY --from=builder /flatcc/lib/*.a /usr/local/lib/


# Source Code (flatcc)
# ====================
COPY --from=builder /flatcc.tar.gz flatcc.tar.gz
RUN tar xzf flatcc.tar.gz \
    && mkdir -p /usr/local/src \
    && mv flatcc-* /usr/local/src/flatcc \
    && rm flatcc.tar.gz


# CMD ["/bin/bash", "-c", "tail /dev/null -f"]
