add_library(RipsawEngine2D STATIC
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

target_link_libraries(RipsawEngine2D PUBLIC
  SDL3::SDL3
  SDL3_image::SDL3_image
  SDL3_ttf::SDL3_ttf
)

add_library(RipsawEngine3D STATIC
  src/3D/Engine.cxx
)

apply_strict_flags(RipsawEngine3D)

set_target_properties(RipsawEngine3D PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  INTERPROCEDURAL_OPTIMIZATION TRUE
)

target_include_directories(RipsawEngine3D PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(LINUX)
  target_link_libraries(RipsawEngine3D PUBLIC
    SDL3::SDL3
    glad_gl_core_43
  )
elseif(ANDROID)
  target_link_libraries(RipsawEngine3D PUBLIC
    SDL3::SDL3
    glad_gles2_core_32
  )
endif()

