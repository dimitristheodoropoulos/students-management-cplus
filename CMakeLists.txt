cmake_minimum_required(VERSION 3.16)
project(StudentsManagementSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Paths ---
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build")

# --- Include directories ---
include_directories(${INCLUDE_DIR})

# --- Main executable ---
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")
add_executable(student_management ${SRC_FILES})
set_target_properties(student_management PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)

# --- GoogleTest setup ---
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# --- Test executable ---
file(GLOB TEST_FILES "${TESTS_DIR}/*.cpp")
add_executable(test_student_manager ${TEST_FILES} ${SRC_FILES})
target_link_libraries(test_student_manager GTest::GTest GTest::Main pthread)
set_target_properties(test_student_manager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)

add_test(NAME StudentManagerTests COMMAND test_student_manager)

# --- Optional: convenience target for building all ---
add_custom_target(all_build ALL
    DEPENDS student_management test_student_manager
)
