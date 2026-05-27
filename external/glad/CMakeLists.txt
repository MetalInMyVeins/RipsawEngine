if(RIPSAW_ENGINE_BACKEND_GLCORE43)
  add_subdirectory(glad-glcore4.3)
elseif(RIPSAW_ENGINE_BACKEND_GLES2CORE32)
  add_subdirectory(glad-gles2core3.2)
endif()

