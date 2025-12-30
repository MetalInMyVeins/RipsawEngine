add_executable(sandbox src/main.cxx)

set_target_properties(sandbox PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

target_link_libraries(sandbox PRIVATE RipsawEngine)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(
    TARGET sandbox POST_BUILD
    COMMAND /usr/bin/strip "$<TARGET_FILE:sandbox>"
    COMMENT "Stripping symbols..."
  )
  add_custom_command(
    TARGET sandbox POST_BUILD
    COMMAND /usr/bin/upx --best "$<TARGET_FILE:sandbox>"
    COMMENT "Compressing binary..."
  )
endif()

