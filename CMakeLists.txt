cmake_minimum_required(VERSION 3.15...3.20)

# +---------------+
# | Project setup |
# +---------------+

project(
  hufflepuffle
  VERSION 0.1.1
  DESCRIPTION "Implementing a Huffman Coding algorithm"
  HOMEPAGE_URL "https://github.com/rufus-stone/hufflepuffle"
  LANGUAGES CXX)

# Create our executable
add_executable(${PROJECT_NAME} src/main.cpp src/huffle.cpp)

# We're using C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Set compiler warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -W4 -WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra
                                                 -Wold-style-cast -Wpedantic)
endif()

# Add the include directory to the target
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

# +--------------+
# | Dependencies |
# +--------------+

# Download Conan script if needed
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    EXPECTED_HASH
      SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
    TLS_VERIFY ON)
endif()

# Load the Conan script
include(${CMAKE_BINARY_DIR}/conan.cmake)

# Configure Conan to grab our dependencies
conan_cmake_configure(REQUIRES spdlog/1.8.5 GENERATORS cmake_find_package)

# Do some settings stuff??
conan_cmake_autodetect(settings)

# Install the dependencies
conan_cmake_install(
  PATH_OR_REFERENCE
  .
  BUILD
  missing
  REMOTE
  conan-center
  SETTINGS
  ${settings})

# This is necessary otherwise find_package() doesn't look in the right place for
# the conan dependencies
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Find the Conan dependencies
find_package(spdlog REQUIRED)

# Hamarr
find_package(hamarr CONFIG REQUIRED)

# Link libraries to executable
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog hamarr::hamarr)

# +-------+
# | Tests |
# +-------+

# Enable testing
include(CTest)
message("BUILD_TESTING: ${BUILD_TESTING}")
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
