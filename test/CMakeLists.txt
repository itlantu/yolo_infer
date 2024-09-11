project(yolo_infer_test)

message(STATUS "")
message(STATUS "--- test ---")

set(cv_dir      "${CMAKE_CURRENT_SOURCE_DIR}/cv")
set(core_dir    "${CMAKE_CURRENT_SOURCE_DIR}/core")
set(onnx_dir    "${CMAKE_CURRENT_SOURCE_DIR}/onnx")

# opencv
utils_add_test_file("${cv_dir}/sample.cpp"          LINK OpenCV)
utils_add_test_file("${cv_dir}/resize.cpp"          LINK OpenCV)
# src/core
utils_add_test_file("${core_dir}/shape.cpp"         LINK SRC)
utils_add_test_file("${core_dir}/tensor_type.cpp"   LINK SRC)
utils_add_test_file("${core_dir}/tensor.cpp"        LINK SRC)
# onnx
utils_add_test_file("${onnx_dir}/providers.cpp"     LINK ONNXRuntime)
utils_add_test_file("${onnx_dir}/info.cpp"          LINK ONNXRuntime SRC)