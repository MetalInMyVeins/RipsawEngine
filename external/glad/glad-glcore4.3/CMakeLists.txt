add_library(glad_gl_core_43 STATIC
  src/glad.c
)

set_target_properties(glad_gl_core_43 PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  INTERPROCEDURAL_OPTIMIZATION TRUE
)

apply_looser_flags(glad_gl_core_43)

target_include_directories(glad_gl_core_43 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

