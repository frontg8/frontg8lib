set(CUTE_GROUP "${CUTE_GROUP}::message")

cute_test(encrypted_api
  LIBRARIES frontg8 ${CONAN_LIBS}
  )

