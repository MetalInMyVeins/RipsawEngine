# RipsawEngine

2D/3D game engine being implemented from scratch in C++. This is a pet project and I work on it in my free time, for fun. Grew up playing lots of games and it's been quite some time I have been wishing to write my own engine. As I enjoy understanding and working on complex systems, this is the perfect type of project to have fun from. So, seeing where it goes.

# Dependencies

- SDL3
- GLM
- GCC/Clang/Any C++ 20 compatible compiler
- CMake

### Optional Dependencies

- Doxygen (for documentation)
- GNU `tree` (for directory layout)
- Ninja (for faster build)
- Python 3 (for parsing documentation)
- GNU Binutils (for `strip`)
- `upx` (for compressing binary)
- `libc++` (for better compliance with sanitizers)
- `libc++abi`
- `lld` (for clang-specific builds)
- `valgrind` (for leak detection)

# Directory Layout

<!-- AUTODOC:BEGIN -->
<!-- AUTODOC:END -->

# Project Components

- `engine/`: All engine code goes here.
- `sandbox/`: All engine feature testing code goes here.
- `scripts/`: All supplementary scripts go here.

# Features

Features in the engine are added incrementally. And each commit contains a demo of the feature in sandbox which can be built and run. Engine is still in zygote phase, so not a lot of features as of now. The notable features for now include but are not limited to:

- Actor-Component system
- Strong ownership model
- Clear separation of engine code and game code
- 2D rendering pipeline
- Flexible but strict build system
- Sanitizer-aware debug builds by default (ASan, UBSan, TSan)
- Strict compliance with C++ standard
- Detailed documentation of engine code

# TODO

- Controlled sprite draw order (complete)
- Spritesheet support (complete)
- Sprite animation (in progress)

# Building

`build.sh` is provided for easier building of engine and sandbox demo providing multiple build options. The demo binary path after building is `sandbox/bin/sandbox`. Examples:

```bash
# For debug build with libstdc++ (works well with valgrind)
./build.sh
# For debug build with libc++
./build.sh --libcxx
# For debug build with ASan + UBSan
./build.sh --aubsan
# For debug build with MSan
./build.sh --msan
# For debug build with TSan
./build.sh --tsan
# For release build
./build.sh --release
# For building with gcc (default is clang)
./build.sh --gcc
# For release build with gcc
./build.sh --gcc --release
```

# API Documentation

<!-- AUTODOC:BEGIN -->
<!-- AUTODOC:END -->

# Note

- There is absolutely zero tolerance for any AI generated code in `engine/`. If you want to contribute in the engine, write everything by yourself. `sandbox/` is for testing engine features. You can test in any way you want but no AI generated code in `sandbox/` would be pushed into the main branch. On the other hand, scripts in `scripts/` are just helper scripts unrelated to engine. So, as long as the functionality works properly, anything is acceptable. For example, `scripts/gen_docs.py` is completely AI generated whose functionality is to parse documentation from engine codebase and automatically generate [README.md](README.md).

- All methods and variables in engine must be properly documented abiding by doxygen documentation rules.

# License

Copyright © 2026  Hossain Md. Fahim  <hossainmdfahim66@gmail.com>  
See [LICENSE](./LICENSE.md) for more information.

