add_subdirectory(frontg8/protocol)

add_library(frontg8 SHARED
  $<TARGET_OBJECTS:pb_protocol>
  $<TARGET_OBJECTS:protocol>
  frontg8/lifetime.cpp
  )

target_link_libraries(frontg8 ${CONAN_LIBS})

install(TARGETS frontg8 LIBRARY DESTINATION lib)
