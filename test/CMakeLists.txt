message(STATUS "Building tests...")

add_library(catch_main STATIC catch_main.cpp)

add_executable(${PROJECT_NAME}_tests tests.cpp)

target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_17)

# Add the include directory to the target
target_include_directories(${PROJECT_NAME}_tests
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link libraries to executable
target_link_libraries(${PROJECT_NAME}_tests PRIVATE CONAN_PKG::spdlog)
