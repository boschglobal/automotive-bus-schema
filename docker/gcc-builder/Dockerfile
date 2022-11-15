FROM debian:bullseye-slim AS base


# Setup basic GCC and CMAKE toolchains
# ====================================
RUN apt-get -y update; \
    apt-get -y upgrade; \
    apt-get -y install --no-install-recommends \
        autoconf \
        automake \
        binutils \
        build-essential \
        ca-certificates \
        extra-cmake-modules \
        curl \
        gcc \
        gcc-multilib \
        g++ \
        g++-multilib \
        git \
        jq \
        less \
        libtool \
        make \
        zip \
    && \
    apt-get clean; \
    rm -rf /var/lib/apt/lists/*

RUN curl -fSL https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2-linux-x86_64.sh \
        -o /tmp/cmake-install.sh \
    && chmod u+x /tmp/cmake-install.sh \
    && /tmp/cmake-install.sh --skip-license --prefix=/usr/local \
    && rm /tmp/cmake-install.sh



# =========================
# Construct the final image
# =========================
FROM base AS final

# CMD ["/bin/bash", "-c", "tail /dev/null -f"]
