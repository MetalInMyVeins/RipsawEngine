cmake_minimum_required(VERSION 3.31)
project(Sandbox3D LANGUAGES C CXX)
cmake_policy(SET CMP0135 NEW)
include(FetchContent)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RIPSAW_ENGINE_TARGET_LINUX OFF CACHE BOOL "Choose target linux")
set(RIPSAW_ENGINE_TARGET_WINDOWS OFF CACHE BOOL "Choose target windows")
set(RIPSAW_ENGINE_TARGET_ANDROID OFF CACHE BOOL "Choose target android")
set(RIPSAW_ENGINE_BACKEND_GLCORE43 OFF CACHE BOOL "Choose backend gl_core_43")
set(RIPSAW_ENGINE_BACKEND_GLES2CORE32 OFF CACHE BOOL "Choose backend gles2_core_32")
set(RIPSAW_ENGINE_SUBSYSTEM_2D OFF CACHE BOOL "Choose 2D subsystem")
set(RIPSAW_ENGINE_SUBSYSTEM_3D OFF CACHE BOOL "Choose 3D subsytem")

set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE)
set(SDLIMAGE_VENDORED ON CACHE BOOL "" FORCE)
set(SDLIMAGE_ANI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP ON CACHE BOOL "" FORCE)
set(SDLIMAGE_GIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG ON CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG_VENDORED ON CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_LBM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PCX OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG ON CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG_VENDORED ON CACHE BOOL "" FORCE)
set(SDLIMAGE_PNM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_QOI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_SVG OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TGA OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XCF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XPM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XV OFF CACHE BOOL "" FORCE)
set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)

set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.deps)

foreach(dep IN ITEMS SDL3-src SDL3_image-src SDL3_ttf-src)
  if(NOT EXISTS ${DEPS_DIR}/${dep}/CMakeLists.txt)
    message(FATAL_ERROR
      ".deps/${dep} not found or incomplete. "
      "Run the fetch script first: scripts/fetch_deps.sh")
  endif()
endforeach()

add_subdirectory(${DEPS_DIR}/SDL3-src)
if(RIPSAW_ENGINE_SUBSYSTEM_2D)
  add_subdirectory(${DEPS_DIR}/SDL3_image-src)
  add_subdirectory(${DEPS_DIR}/SDL3_ttf-src)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_link_options(-fuse-ld=lld)
endif()

function(apply_strict_flags target)
  target_compile_options(${target} PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -Wformat=2
    -Wundef
    -Wcast-align
    -Wcast-qual
    -Wdouble-promotion
    -Wnull-dereference
    -Wold-style-cast
    -Woverloaded-virtual
    -Wnon-virtual-dtor
    -Wimplicit-fallthrough
    -Wredundant-decls
    -Wswitch-enum
    -Wzero-as-null-pointer-constant
    -fno-rtti
    $<$<CONFIG:Release>:
      -O3
      -fvisibility=hidden
      -fomit-frame-pointer
      -fcf-protection=full
      -fstack-clash-protection
      -D_FORTIFY_SOURCE=3
      -DNDEBUG
    >
  )
endfunction()

function(apply_loose_flags target)
  target_compile_options(${target} PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wno-unused-variable
    -Wno-unused-but-set-variable
    -Wno-unused-private-field
    -Wno-unused-parameter
  )
endfunction()

function(apply_looser_flags target)
  target_compile_options(${target} PUBLIC
    -Wall
  )
endfunction()

add_subdirectory(external)
add_subdirectory(src)

