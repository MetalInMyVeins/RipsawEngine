if(RIPSAW_ENGINE_TARGET_LINUX OR RIPSAW_ENGINE_TARGET_WINDOWS OR RIPSAW_ENGINE_TARGET_ANDROID)
  add_library(glad_gles2_core_32 SHARED
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
endif()

