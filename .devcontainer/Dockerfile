# PlatformIO development image for the Smoggy ESP32 firmware.
FROM python:3.12-bookworm

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=1000

ENV DEBIAN_FRONTEND=noninteractive
ENV PLATFORMIO_CORE_DIR=/home/${USERNAME}/.platformio

# Tools used by PlatformIO itself (git/curl for dependencies), by the
# serial monitor, and by users while debugging USB/serial devices.
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        curl \
        git \
        libusb-1.0-0 \
        picocom \
        sudo \
        udev \
        usbutils \
    && rm -rf /var/lib/apt/lists/*

# Pin PlatformIO Core so image rebuilds stay reproducible. Bump it here when
# you intentionally want a newer Core.
RUN pip install --no-cache-dir "platformio==6.2.0"

# Non-root development user. Membership in dialout grants access to
# /dev/ttyUSB* and /dev/ttyACM* serial adapters.
RUN groupadd --gid "${USER_GID}" "${USERNAME}" \
    && useradd --uid "${USER_UID}" --gid "${USER_GID}" \
        --create-home --shell /bin/bash "${USERNAME}" \
    && groupadd --force dialout \
    && usermod --append --groups dialout "${USERNAME}" \
    && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" \
        > "/etc/sudoers.d/${USERNAME}" \
    && chmod 0440 "/etc/sudoers.d/${USERNAME}" \
    && mkdir -p "${PLATFORMIO_CORE_DIR}" \
    && chown -R "${USERNAME}:${USERNAME}" "/home/${USERNAME}"

USER ${USERNAME}
WORKDIR /workspaces
