add_library(frontg8 SHARED $<TARGET_OBJECTS:pb_protocol>)
target_link_libraries(frontg8 ${CONAN_LIBS})
install(TARGETS frontg8 LIBRARY DESTINATION lib)
