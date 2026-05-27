if(RIPSAW_ENGINE_SUBSYSTEM_2D)
  add_library(RipsawEngine2D SHARED
    src/2D/Actor.cxx
    src/2D/BGManager.cxx
    src/2D/Component.cxx
    src/2D/Engine.cxx
    src/2D/Game.cxx
    src/2D/SpriteComponent.cxx
    src/2D/SpritesheetComponent.cxx
    src/2D/Timer.cxx
    src/2D/TransformComponent.cxx
    src/2D/processInput.cxx
    src/2D/renderEngine.cxx
    src/2D/updateEngine.cxx
  )

  target_compile_definitions(RipsawEngine2D PUBLIC
    $<$<BOOL:${RIPSAW_ENGINE_TARGET_LINUX}>:RIPSAW_ENGINE_TARGET_LINUX>
    $<$<BOOL:${RIPSAW_ENGINE_TARGET_WINDOWS}>:RIPSAW_ENGINE_TARGET_WINDOWS>
    $<$<BOOL:${RIPSAW_ENGINE_TARGET_ANDROID}>:RIPSAW_ENGINE_TARGET_ANDROID>
    $<$<BOOL:${RIPSAW_ENGINE_BACKEND_GLCORE43}>:RIPSAW_ENGINE_BACKEND_GLCORE43>
    $<$<BOOL:${RIPSAW_ENGINE_BACKEND_GLES2CORE32}>:RIPSAW_ENGINE_BACKEND_GLES2CORE32>
    $<$<BOOL:${RIPSAW_ENGINE_SUBSYSTEM_2D}>:RIPSAW_ENGINE_SUBSYSTEM_2D>
    $<$<BOOL:${RIPSAW_ENGINE_SUBSYSTEM_3D}>:RIPSAW_ENGINE_SUBSYSTEM_3D>
  )

  apply_strict_flags(RipsawEngine2D)

  set_target_properties(RipsawEngine2D PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    INTERPROCEDURAL_OPTIMIZATION TRUE
  )

  target_include_directories(RipsawEngine2D PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

  if(RIPSAW_ENGINE_TARGET_LINUX OR RIPSAW_ENGINE_TARGET_WINDOWS)
    target_link_libraries(RipsawEngine2D PUBLIC
      SDL3::SDL3
      SDL3_image::SDL3_image
      SDL3_ttf::SDL3_ttf
    )
  elseif(RIPSAW_ENGINE_TARGET_ANDROID)
    target_include_directories(RipsawEngine2D PUBLIC
      ${CMAKE_SOURCE_DIR}/.deps/glm-src
    )
    target_link_libraries(RipsawEngine2D PUBLIC
      SDL3::SDL3
      SDL3_image::SDL3_image
      SDL3_ttf::SDL3_ttf
      android
      EGL
      GLESv2
      log
    )
  endif()
elseif(RIPSAW_ENGINE_SUBSYSTEM_3D)
  add_library(RipsawEngine3D SHARED
    src/3D/Engine.cxx
    src/3D/readFile.cxx
  )

  add_library(stbimg SHARED
    src/3D/stb_impl.cxx
  )

  target_compile_definitions(RipsawEngine3D PUBLIC
    $<$<BOOL:${RIPSAW_ENGINE_TARGET_LINUX}>:RIPSAW_ENGINE_TARGET_LINUX>
    $<$<BOOL:${RIPSAW_ENGINE_TARGET_WINDOWS}>:RIPSAW_ENGINE_TARGET_WINDOWS>
    $<$<BOOL:${RIPSAW_ENGINE_TARGET_ANDROID}>:RIPSAW_ENGINE_TARGET_ANDROID>
    $<$<BOOL:${RIPSAW_ENGINE_BACKEND_GLCORE43}>:RIPSAW_ENGINE_BACKEND_GLCORE43>
    $<$<BOOL:${RIPSAW_ENGINE_BACKEND_GLES2CORE32}>:RIPSAW_ENGINE_BACKEND_GLES2CORE32>
    $<$<BOOL:${RIPSAW_ENGINE_SUBSYSTEM_2D}>:RIPSAW_ENGINE_SUBSYSTEM_2D>
    $<$<BOOL:${RIPSAW_ENGINE_SUBSYSTEM_3D}>:RIPSAW_ENGINE_SUBSYSTEM_3D>
  )

  apply_strict_flags(RipsawEngine3D)
  apply_no_flags(stbimg)

  set_target_properties(RipsawEngine3D PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    INTERPROCEDURAL_OPTIMIZATION TRUE
  )
  set_target_properties(stbimg PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    INTERPROCEDURAL_OPTIMIZATION TRUE
  )

  target_include_directories(RipsawEngine3D PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_include_directories(stbimg PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

  if(RIPSAW_ENGINE_TARGET_LINUX OR RIPSAW_ENGINE_TARGET_WINDOWS)
    target_link_libraries(RipsawEngine3D PUBLIC
      SDL3::SDL3
      glad_gl_core_43
      stbimg
    )
  elseif(RIPSAW_ENGINE_TARGET_ANDROID)
    target_link_libraries(RipsawEngine3D PUBLIC
      SDL3::SDL3
      glad_gles2_core_32
      stbimg
      android
      EGL
      GLESv2
      log
    )
  endif()
endif()

