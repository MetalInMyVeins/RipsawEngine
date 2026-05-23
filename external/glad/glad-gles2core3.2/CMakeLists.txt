add_library(glad_gles2_core_32 STATIC
  src/glad.c
)

set_target_properties(glad_gles2_core_32 PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  INTERPROCEDURAL_OPTIMIZATION TRUE
)

apply_looser_flags(glad_gles2_core_32)

target_include_directories(glad_gles2_core_32 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

