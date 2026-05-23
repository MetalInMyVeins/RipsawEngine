cmake_minimum_required(VERSION 3.21)
project(RipsawEngine LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(USE_LIBCXX "Use libc++ instead of libstdc++" OFF)
option(ENABLE_SANITIZERS_ADDUB "Enable Address + Undefined sanitizers" OFF)
option(ENABLE_SANITIZERS_MEMUB "Enable Memory + Undefined sanitizers" OFF)
option(ENABLE_SANITIZERS_THREAD "Enable Thread sanitizer" OFF)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND USE_LIBCXX)
  add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-stdlib=libc++>)
  add_link_options(-stdlib=libc++ -lc++ -lc++abi)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_link_options(-fuse-ld=lld)
endif()

set(SANITIZER_COUNT 0)
if(ENABLE_SANITIZERS_ADDUB)
  math(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
endif()
if(ENABLE_SANITIZERS_MEMUB)
  math(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
endif()
if(ENABLE_SANITIZERS_THREAD)
  math(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
endif()

if(SANITIZER_COUNT GREATER 1)
  message(FATAL_ERROR "Only one sanitizer option can be enabled at a time")
endif()

if(ENABLE_SANITIZERS_ADDUB OR ENABLE_SANITIZERS_MEMUB OR ENABLE_SANITIZERS_THREAD)
  if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(FATAL_ERROR "Sanitizers are only supported in Debug builds")
  endif()
endif()

if(ENABLE_SANITIZERS_ADDUB)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
  endif()
elseif(ENABLE_SANITIZERS_MEMUB)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-g -O0 -fsanitize=memory,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=memory,undefined)
  endif()
elseif(ENABLE_SANITIZERS_THREAD)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-g -O0 -fsanitize=thread -fno-omit-frame-pointer)
    add_link_options(-fsanitize=thread)
  endif()
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type specified. Setting to Debug.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type specified. Setting to Debug.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE)
set(SDLIMAGE_VENDORED ON CACHE BOOL "" FORCE)
set(SDLIMAGE_ANI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP ON CACHE BOOL "" FORCE)
set(SDLIMAGE_GIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG ON CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_LBM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PCX OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG ON CACHE BOOL "" FORCE)
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

add_subdirectory(external)
add_subdirectory(engine)
add_subdirectory(sandbox)

