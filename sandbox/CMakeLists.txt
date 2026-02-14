add_executable(sandboxbin src/main.cxx)

set_target_properties(sandboxbin PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  INSTALL_RPATH "$ORIGIN"
  BUILD_WITH_INSTALL_RPATH ON
)

target_link_libraries(sandboxbin PRIVATE RipsawEngine)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(
    TARGET sandboxbin POST_BUILD
    COMMAND /usr/bin/strip "$<TARGET_FILE:sandboxbin>"
    COMMENT "Stripping symbols..."
  )
  add_custom_command(
    TARGET sandboxbin POST_BUILD
    COMMAND /usr/bin/upx --best "$<TARGET_FILE:sandboxbin>"
    COMMENT "Compressing binary..."
  )
endif()

install(TARGETS sandboxbin
  RUNTIME DESTINATION .
)

install(TARGETS RipsawEngine
  LIBRARY DESTINATION .
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/sandbox/assets
  DESTINATION .
)

