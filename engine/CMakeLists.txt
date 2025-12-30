if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(LIB_TYPE STATIC)
else()
  set(LIB_TYPE SHARED)
endif()

add_library(RipsawEngine ${LIB_TYPE}
  src/Actor.cxx
  src/BGManager.cxx
  src/Component.cxx
  src/Engine.cxx
  src/Game.cxx
  src/SpriteComponent.cxx
  src/TransformComponent.cxx
  src/processInput.cxx
  src/renderEngine.cxx
  src/updateEngine.cxx
)

set_target_properties(RipsawEngine PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
  INTERPROCEDURAL_OPTIMIZATION TRUE
)

target_include_directories(RipsawEngine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(RipsawEngine PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror
  -Wshadow
  -Wconversion
  -Wsign-conversion
  -Wformat=2
  -Wundef
)

target_compile_options(RipsawEngine PRIVATE
  $<$<CONFIG:Release>:
    -O3
    -fvisibility=hidden
    -fomit-frame-pointer
    -fcf-protection=full
    -fstack-clash-protection
    -D_FORTIFY_SOURCE=3
    -DNDEBUG
  >
)

target_link_options(RipsawEngine PRIVATE
  $<$<CONFIG:Release>:
    -flto
    -pie
    -Wl,-z,relro,-z,now
  >
)

target_link_libraries(RipsawEngine PRIVATE
  SDL3 SDL3_image SDL3_ttf
)

