set(CUTE_GROUP "api")

cute_test(error_c_api
  LIBRARIES frontg8 ${CONAN_LIBS}
  )

cute_test(error_cpp_api
  LIBRARIES frontg8 ${CONAN_LIBS}
  )

add_subdirectory(protocol)
