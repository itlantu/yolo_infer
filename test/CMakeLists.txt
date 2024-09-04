project(yolo_infer_test)

message(STATUS " ")

add_executable(test_cv_project
        "${CMAKE_CURRENT_SOURCE_DIR}/cv/sample.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/cv/resize.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/cv/main.cpp"
)

add_executable(test_core_project
        "${CMAKE_CURRENT_SOURCE_DIR}/core/shape.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/core/main.cpp"
)

TEST_PROJECT(test_cv    test_cv_project     1)
TEST_PROJECT(test_core  test_core_project   2)