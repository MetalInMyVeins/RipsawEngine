add_library(glad_gl_core_43 SHARED
  src/glad.c
)

apply_looser_flags(glad_gl_core_43)

target_include_directories(glad_gl_core_43 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

