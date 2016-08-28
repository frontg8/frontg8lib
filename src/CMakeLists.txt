add_subdirectory(impl)
add_subdirectory(frontg8)

add_library(frontg8 SHARED
  $<TARGET_OBJECTS:pb_protocol>
  $<TARGET_OBJECTS:protocol_impl>
  $<TARGET_OBJECTS:utility_impl>
  $<TARGET_OBJECTS:utility>
  $<TARGET_OBJECTS:protocol>
  )

target_link_libraries(frontg8 ${CONAN_LIBS})

install(TARGETS frontg8 LIBRARY DESTINATION lib)

add_subdirectory(demo)
