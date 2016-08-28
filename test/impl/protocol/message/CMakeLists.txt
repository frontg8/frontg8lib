set(CUTE_GROUP "${CUTE_GROUP}::message")

cute_test(encrypted_impl
  DEPENDENCIES $<TARGET_OBJECTS:pb_protocol> $<TARGET_OBJECTS:protocol_impl>
  LIBRARIES ${CONAN_LIBS}
  )

