add_library(RipsawEngine STATIC
  src/Actor.cxx
  src/Component.cxx
  src/Engine.cxx
  src/TransformComponent.cxx
  src/processInput.cxx
  src/renderEngine.cxx
  src/updateEngine.cxx
)

set_target_properties(RipsawEngine PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_include_directories(RipsawEngine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(RipsawEngine PRIVATE
  $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Debug>>:${DEBUG_C_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:${DEBUG_CXX_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Release>>:${RELEASE_C_FLAGS}>
  $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:${RELEASE_CXX_FLAGS}>
)

target_link_libraries(RipsawEngine PRIVATE
  SDL3 SDL3_image SDL3_ttf
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(
    TARGET RipsawEngine POST_BUILD
    COMMAND ${CMAKE_STRIP} "$<TARGET_FILE:RipsawEngine>"
    COMMENT "Stripping symbols..."
  )
  add_custom_command(
    TARGET RipsawEngine POST_BUILD
    COMMAND upx --best "$<TARGET_FILE:RipsawEngine>"
    COMMENT "Compressing binary..."
  )
endif()

