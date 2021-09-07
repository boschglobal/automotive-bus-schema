FROM python:3.8.10-slim


# Setup basic tools
# =================
RUN apt-get -y update; \
    apt-get -y upgrade; \
    apt-get -y install --no-install-recommends \
        build-essential \
        ca-certificates \
        cargo \
        curl \
        gcc \
        git \
        less \
        make \
        python3-dev \
        zip \
    && \
    apt-get clean; \
    rm -rf /var/lib/apt/lists/*


# Python VENV
# ===========
RUN python -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"


# Python Libraries
# ================
RUN pip install --upgrade pip; pip install \
        flatbuffers==1.12 \
        msgpack \
        numpy \
        pip-licenses \
        pytest \
        twine \
        wheel \
    && \
    pip list; pip-licenses


# Global PIP config
# =================
COPY pip.conf /etc/pip.conf


# CMD ["/bin/bash", "-c", "tail /dev/null -f"]
