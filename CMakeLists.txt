cmake_minimum_required(VERSION 3.0)
project(frontg8lib
  LANGUAGES CXX
  VERSION 0.1.0
  )

# Export the compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS On CACHE BOOL "Export compilation commands" FORCE)

# Add our custom modules to the module search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Default to building the 'Release' configuration
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "The build configuration" FORCE)
endif()

# Set basic compiler flags.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -std=c++14 -fPIC -fvisibility=hidden -fdata-sections -ffunction-sections")

# Enable debug symbols for 'Debug' builds
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Enable optimization for 'Release' builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Set release flags for libraries
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-Wl,--gc-sections,--as-needed")

# Include support for the Clang sanitizer infrastructure
include(ClangSanitizers)

# Prepare Conan.io packages
set(CONAN_BUILD_INFO_FILE ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
if(NOT EXISTS ${CONAN_BUILD_INFO_FILE})
  message(STATUS "No conan package information available. Trying to fix that!")
  execute_process(COMMAND conan install --build=missing ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_QUIET)
endif()

# Import dependencies via Conan.io
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CONAN_SYSTEM_INCLUDES On)
conan_basic_setup()

# Generate protcol buffer cpp files
include(GenerateProtobufSource)

# Define the output directory for 'Release' builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/products/Release/bin" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/products/Release/lib" CACHE PATH "" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/products/Release/lib" CACHE PATH "" FORCE)

# Define the output directory for 'Debug' builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/products/Debug/bin" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/products/Debug/lib" CACHE PATH "" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/products/Debug/lib" CACHE PATH "" FORCE)

# Add project includes to header search path
include_directories(include)
include_directories(SYSTEM protobuf)

# Include the sources
add_subdirectory(protobuf)
add_subdirectory(include)
add_subdirectory(src)

# Build unittests by default
option(${PROJECT_NAME}_TESTS "Build the unittests" ON)
if(${${PROJECT_NAME}_TESTS})
  # Default to not run the tests during building
  include(CUTE)
  add_definitions(-D${PROJECT_NAME}_TESTING_ENABLED)
  add_subdirectory(test)
endif()

# Enable packaging
set(CPACK_PACKAGE_VENDOR "The frong8 Project")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-dst")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "build/;\\\\.(git.*|ycm_extra_conf.*|color_coded);__pycache__")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-src")
include(CPack)
