set(GENERATED_FILES base.pb.cc
  base.pb.h
  client.pb.cc
  client.pb.h
  server.pb.cc
  server.pb.h)

macro(_pb_check_generated_files RESULT)
  set(${RESULT} YES)

  foreach(PB_FILE IN LISTS GENERATED_FILES)
    if(NOT EXISTS ${PROJECT_SOURCE_DIR}/protobuf/${PB_FILE})
      set(${RESULT} NO)
    endif()
  endforeach()
endmacro()

_pb_check_generated_files(PB_FILES_ARE_GENERATED)
if(NOT ${PB_FILES_ARE_GENERATED})
  message(STATUS "Generating protobuf C++ code...")
  execute_process(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external/frontg8proto/
    COMMAND ${CONAN_BIN_DIRS_PROTOBUF}/protoc --cpp_out=${PROJECT_SOURCE_DIR}/protobuf base.proto client.proto server.proto
    OUTPUT_QUIET
    ERROR_FILE ${CMAKE_CURRENT_BINARY_DIR}/protobuf.log)
  _pb_check_generated_files(PB_FILES_ARE_GENERATED)
  if(NOT ${PB_FILES_ARE_GENERATED})
    message(FATAL_ERROR "Failed to generate protobuf C++ code. Check ${CMAKE_CURRENT_BINARY_DIR}/protobuf.log for more info")
  endif()
endif()

if(NOT TARGET pb_protocol)
  add_library(pb_protocol OBJECT
    ${PROJECT_SOURCE_DIR}/protobuf/base.pb.cc
    ${PROJECT_SOURCE_DIR}/protobuf/client.pb.cc
    ${PROJECT_SOURCE_DIR}/protobuf/server.pb.cc
    )
endif()

include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/protobuf)
