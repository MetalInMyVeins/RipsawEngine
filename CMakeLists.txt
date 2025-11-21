cmake_minimum_required(VERSION 3.21)
project(RipsawEngine)
set(pn ${CMAKE_PROJECT_NAME})
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

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set(DEBUG_C_FLAGS
  -g -Wall -Wextra -Wpedantic -Werror
)
set(DEBUG_CXX_FLAGS
  -g -Wall -Wextra -Wpedantic -Werror
  -Wno-unused-parameter -Wno-unused-private-field -Wno-unused-variable
)
set(RELEASE_C_FLAGS
  -Wall -Wextra -Wpedantic -Werror
  -O3 -flto -ffast-math -march=native -mtune=native -fomit-frame-pointer -funroll-loops -fno-stack-protector
  -fvisibility=hidden -fcf-protection=full -fstack-clash-protection -D_FORTIFY_SOURCE=3 -fPIE
)
set(RELEASE_CXX_FLAGS
  -Wall -Wextra -Wpedantic -Werror
  -Wno-unused-parameter -Wno-unused-private-field -Wno-unused-variable
  -O3 -flto -ffast-math -march=native -mtune=native -fomit-frame-pointer -funroll-loops -fno-stack-protector
  -fvisibility=hidden -fcf-protection=full -fstack-clash-protection -D_FORTIFY_SOURCE=3 -fPIE
)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type specified. Setting to Debug.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

add_library(lib${pn} STATIC
  ${CMAKE_SOURCE_DIR}/src/dummy.cxx
)
target_compile_options(lib${pn} PRIVATE
  $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Debug>>:${DEBUG_C_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:${DEBUG_CXX_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Release>>:${RELEASE_C_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:${RELEASE_CXX_FLAGS}>
)

add_executable(${pn} ${CMAKE_SOURCE_DIR}/src/main.cxx)
target_compile_options(${pn} PRIVATE
  $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Debug>>:${DEBUG_C_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:${DEBUG_CXX_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Release>>:${RELEASE_C_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:${RELEASE_CXX_FLAGS}>
)
target_link_libraries(${pn} lib${pn} SDL3 SDL3_image SDL3_ttf)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(
    TARGET ${pn} POST_BUILD
    COMMAND /usr/bin/strip "$<TARGET_FILE:${pn}>"
    COMMENT "stripping..."
  )
  add_custom_command(
    TARGET ${pn} POST_BUILD
    COMMAND /usr/bin/upx --best "$<TARGET_FILE:${pn}>"
    COMMENT "compressing..."
  )
endif()

message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Selected C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Selected C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Executable Path: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "Library Path: ${LIBRARY_OUTPUT_PATH}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

set_target_properties(lib${pn} PROPERTIES
  OUTPUT_NAME ${pn}
)

