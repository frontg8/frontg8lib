set(CUTE_GROUP "${CUTE_GROUP}::message")

cute_test(encrypted_c_api
  LIBRARIES frontg8 ${CONAN_LIBS}
  )

cute_test(encrypted_cpp_api
  LIBRARIES frontg8 ${CONAN_LIBS}
  )

