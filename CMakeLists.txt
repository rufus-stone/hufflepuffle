cmake_minimum_required(VERSION 3.15...3.19)

# +---------------+
# | Project setup |
# +---------------+

project(
  hufflepuffle
  VERSION 0.1.0
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

# +--------------+
# | Dependencies |
# +--------------+

# Conan scripts
include(${PROJECT_SOURCE_DIR}/cmake/conan.cmake)

# Pull in the conan dependencies
conan_cmake_run(REQUIRES spdlog/1.8.2 BASIC_SETUP CMAKE_TARGETS BUILD missing)

# Hamarr
find_package(hamarr CONFIG REQUIRED)

# Add the include directory to the target
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link libraries to executable
target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::spdlog hamarr::hamarr)

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
