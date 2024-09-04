project(yolo_infer_test)

message(STATUS " ")

add_executable(test_cv_project
        "${CMAKE_CURRENT_SOURCE_DIR}/cv/sample.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/cv/resize.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/cv/main.cpp"
)
TARGET_LINK_ALL_LIBRARY(test_cv_project)

message(STATUS "Test 1) cv - test: running")
add_test(test_cv test_cv_project)
message(STATUS "Test 1) cv - test: end")