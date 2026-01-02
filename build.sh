#!/bin/bash

# For debug build with libstdc++ (works well with valgrind)
# $ ./build.sh
# For debug build with libc++
# $ ./build.sh --libcxx
# For debug build with ASan + UBSan
# ./build.sh --aubsan
# For debug build with MSan
# ./build.sh --msan
# For debug build with TSan
# ./build.sh --tsan
# For release build
# ./build.sh --release
# For building with gcc (default is clang)
# ./build.sh --gcc
# For release build with gcc
# ./build.sh --gcc --release

CMAKE_C_COMPILER=clang
CMAKE_CXX_COMPILER=clang++
BUILD_TYPE=Debug
USE_LIBCXX=OFF
SAN_ADDUB=OFF
SAN_MEMUB=OFF
SAN_THREAD=OFF
BUILD_DIR=build
USE_NINJA=OFF

for arg in "$@"; do
  case "$arg" in
    --gcc)
      CMAKE_C_COMPILER=gcc
      CMAKE_CXX_COMPILER=g++
      ;;
    --libcxx)
      USE_LIBCXX=ON
      ;;
    --aubsan)
      SAN_ADDUB=ON
      USE_LIBCXX=ON
      ;;
    --msan)
      SAN_MEMUB=ON
      USE_LIBCXX=ON
      ;;
    --tsan)
      SAN_THREAD=ON
      USE_LIBCXX=ON
      ;;
    --release)
      BUILD_TYPE=Release
      ;;
    *)
      echo "Unknown option: $arg"
      exit 1
      ;;
  esac
done

SAN_COUNT=0
[[ "$SAN_ADDUB" == "ON" ]] && ((SAN_COUNT++))
[[ "$SAN_MEMUB" == "ON" ]] && ((SAN_COUNT++))
[[ "$SAN_THREAD" == "ON" ]] && ((SAN_COUNT++))

if [[ "$SAN_COUNT" -gt 1 ]]; then
  echo "Error: Only one sanitizer can be enabled at a time."
  exit 1
fi

if [[ "$SAN_COUNT" -eq 1 && "$BUILD_TYPE" != "Debug" ]]; then
  echo "Error: Sanitizers are only supported in Debug builds."
  exit 1
fi

CMAKE_GENERATOR_ARGS=()
if command -v ninja >/dev/null 2>&1; then
  USE_NINJA=ON
  CMAKE_GENERATOR_ARGS=(-G Ninja)
fi

mkdir -p "$BUILD_DIR"

cmake -S . -B "$BUILD_DIR" \
  "${CMAKE_GENERATOR_ARGS[@]}" \
  -DCMAKE_C_COMPILER="$CMAKE_C_COMPILER" \
  -DCMAKE_CXX_COMPILER="$CMAKE_CXX_COMPILER" \
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
  -DUSE_LIBCXX="$USE_LIBCXX" \
  -DENABLE_SANITIZERS_ADDUB="$SAN_ADDUB" \
  -DENABLE_SANITIZERS_MEMUB="$SAN_MEMUB" \
  -DENABLE_SANITIZERS_THREAD="$SAN_THREAD"

if [[ "$USE_NINJA" == "ON" ]]; then
  ninja -C "$BUILD_DIR"
else
  cmake --build "$BUILD_DIR" --parallel
fi

