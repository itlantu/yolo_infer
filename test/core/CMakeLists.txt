project(core_shape)
project(core_tensor_type)

add_executable(core_shape "shape.cpp")
add_executable(core_tensor_type "tensor_type.cpp")

utils_test_project(core_shape 3)
utils_test_project(core_tensor_type 4)