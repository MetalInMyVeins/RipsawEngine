cmake_minimum_required(VERSION 3.21)
project(RipsawEngine LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type specified. Setting to Debug.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(DEBUG_C_FLAGS -g -Wall -Wextra -Wpedantic -Werror)
set(DEBUG_CXX_FLAGS -g -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-private-field -Wno-unused-variable)
set(RELEASE_C_FLAGS -Wall -Wextra -Wpedantic -Werror -O3 -flto -ffast-math -march=native -mtune=native -fomit-frame-pointer -funroll-loops -fno-stack-protector -fvisibility=hidden -fcf-protection=full -fstack-clash-protection -D_FORTIFY_SOURCE=3 -fPIE)
set(RELEASE_CXX_FLAGS -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-private-field -Wno-unused-variable -O3 -flto -ffast-math -march=native -mtune=native -fomit-frame-pointer -funroll-loops -fno-stack-protector -fvisibility=hidden -fcf-protection=full -fstack-clash-protection -D_FORTIFY_SOURCE=3 -fPIE)

add_subdirectory(engine)
add_subdirectory(sandbox)

