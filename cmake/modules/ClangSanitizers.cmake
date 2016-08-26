if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  option(WITH_LEAK_SANITIZER      "Check for memory leaks." OFF)
  option(WITH_ADDRESS_SANITIZER   "Check for typical memory management errors." OFF)
  option(WITH_UNDEFINED_SANITIZER "Check for undefined behaviour." OFF)

  if(WITH_ADDRESS_SANITIZER OR WITH_UNDEFINED_SANITIZER)
    string(APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer")

    set(SANITIZERS "")

    if(WITH_LEAK_SANITIZER)
      list(APPEND SANITIZERS "leak")
    endif()

    if(WITH_ADDRESS_SANITIZER)
      list(APPEND SANITIZERS "address")
    endif()

    if(WITH_UNDEFINED_SANITIZER)
      list(APPEND SANITIZERS "undefined")
    endif()

    string(REPLACE ";" "," SANITIZERS "${SANITIZERS}")
    string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
    set(CMAKE_CXX_FLAGS_${BUILD_TYPE} "${CMAKE_CXX_FLAGS_${BUILD_TYPE}} -fsanitize=${SANITIZERS}")
  endif()
endif()
