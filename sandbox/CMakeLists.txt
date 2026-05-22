add_executable(sandbox2D src/2D/main.cxx)
add_executable(sandbox3D src/3D/main.cxx)

apply_strict_flags(RipsawEngine2D)
apply_strict_flags(RipsawEngine3D)

set_target_properties(sandbox2D PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  INSTALL_RPATH "$ORIGIN"
  BUILD_WITH_INSTALL_RPATH ON
)
set_target_properties(sandbox3D PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  INSTALL_RPATH "$ORIGIN"
  BUILD_WITH_INSTALL_RPATH ON
)

target_link_libraries(sandbox2D PRIVATE RipsawEngine2D)
target_link_libraries(sandbox3D PRIVATE RipsawEngine3D)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(
    TARGET sandbox2D POST_BUILD
    COMMAND /usr/bin/strip "$<TARGET_FILE:sandbox2D>"
    COMMENT "Stripping symbols..."
  )
  add_custom_command(
    TARGET sandbox2D POST_BUILD
    COMMAND /usr/bin/upx --best "$<TARGET_FILE:sandbox2D>"
    COMMENT "Compressing binary..."
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(
    TARGET sandbox3D POST_BUILD
    COMMAND /usr/bin/strip "$<TARGET_FILE:sandbox3D>"
    COMMENT "Stripping symbols..."
  )
  add_custom_command(
    TARGET sandbox3D POST_BUILD
    COMMAND /usr/bin/upx --best "$<TARGET_FILE:sandbox3D>"
    COMMENT "Compressing binary..."
  )
endif()

install(TARGETS sandbox3D
  RUNTIME DESTINATION .
)
install(TARGETS sandbox2D
  RUNTIME DESTINATION .
)

install(TARGETS RipsawEngine2D
  LIBRARY DESTINATION .
)
install(TARGETS RipsawEngine3D
  LIBRARY DESTINATION .
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/sandbox/assets
  DESTINATION .
)

