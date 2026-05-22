add_library(RipsawEngine STATIC
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

set_target_properties(RipsawEngine PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  INTERPROCEDURAL_OPTIMIZATION TRUE
)

target_include_directories(RipsawEngine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RipsawEngine PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
  SDL3_ttf::SDL3_ttf
)

