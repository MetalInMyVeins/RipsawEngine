add_library(glad_gles2_core_32 SHARED
  src/glad.c
)

apply_looser_flags(glad_gles2_core_32)

target_include_directories(glad_gles2_core_32 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

