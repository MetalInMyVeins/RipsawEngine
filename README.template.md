# RipsawEngine

2D/3D game engine being implemented from scratch in C++.

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

# Directory Layout

<!-- AUTODOC:BEGIN -->
<!-- AUTODOC:END -->

# Project Components

- `engine/`: All engine code goes here.
- `sandbox/`: All engine feature testing code goes here.
- `scripts/`: All supplementary scripts go here.

# TODO

- Controlled sprite draw order (complete)
- Spritesheet support (in progress)
- Sprite animation (in progress)

# API Documentation

<!-- AUTODOC:BEGIN -->
<!-- AUTODOC:END -->

# Note

- There is absolutely zero tolerance for any AI generated code in `engine/`. If you want to contribute in the engine, write everything by yourself. `sandbox/` is for testing engine features. You can test in any way you want but no AI generated code in `sandbox/` would be pushed into the main branch. On the other hand, scripts in `scripts/` are just helper scripts unrelated to engine. So, as long as the functionality works properly, anything is acceptable. For example, `scripts/gen_docs.py` is completely AI generated whose functionality is to parse documentation from engine codebase and automatically generate [README.md](README.md).

- All methods and variables in engine must be properly documented abiding by doxygen documentation rules.

# License

Copyright © 2025  Hossain Md. Fahim  <hossainmdfahim66@gmail.com>  
See [LICENSE](./LICENSE.md) for more information.

