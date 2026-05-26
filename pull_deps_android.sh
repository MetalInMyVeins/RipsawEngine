#!/usr/bin/bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEPS_DIR="${SCRIPT_DIR}/platform/android/app/jni/.deps"

mkdir -p "$DEPS_DIR"

# SDL3
if [[ ! -d "${DEPS_DIR}/SDL3-src" ]]; then
    echo "[SDL3] Cloning release-3.4.8 ..."
    git clone --depth 1 --branch release-3.4.8 --progress \
        https://github.com/libsdl-org/SDL.git \
        "${DEPS_DIR}/SDL3-src"
else
    echo "[SDL3] SDL3-src already exists, skipping"
fi

# SDL3_image
if [[ ! -d "${DEPS_DIR}/SDL3_image-src" ]]; then
    echo "[SDL3_image] Cloning release-3.4.4 ..."
    git clone --depth 1 --branch release-3.4.4 --progress \
        https://github.com/libsdl-org/SDL_image.git \
        "${DEPS_DIR}/SDL3_image-src"
    echo "[SDL3_image] Fetching vendored dependencies ..."
    (cd "${DEPS_DIR}/SDL3_image-src/external" && bash download.sh)
else
    echo "[SDL3_image] SDL3_image-src already exists, skipping"
fi

# SDL3_ttf
if [[ ! -d "${DEPS_DIR}/SDL3_ttf-src" ]]; then
    echo "[SDL3_ttf] Cloning release-3.2.2 ..."
    git clone --depth 1 --branch release-3.2.2 --progress \
        https://github.com/libsdl-org/SDL_ttf.git \
        "${DEPS_DIR}/SDL3_ttf-src"
    echo "[SDL3_ttf] Fetching SDL3_ttf vendored dependencies ..."
    (cd "${DEPS_DIR}/SDL3_ttf-src/external" && bash download.sh)
else
    echo "[SDL3_ttf] SDL3_ttf-src already exists, skipping"
fi

# GLM
if [[ ! -d "${DEPS_DIR}/glm-src" ]]; then
    echo "[GLM] Cloning 1.0.3 ..."
    git clone --depth 1 --branch 1.0.3 --progress \
        https://github.com/g-truc/glm \
        "${DEPS_DIR}/glm-src"
    echo "[GLM] Fetching GLM vendored dependencies ..."
else
    echo "[GLM] glm-src already exists, skipping"
fi

echo ""
echo "[SUCESS] Done. All sources ready in: ${DEPS_DIR}"

