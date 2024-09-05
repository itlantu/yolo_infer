project(core_shape)
project(core_tensor_type)
project(core_tensor)

add_executable(core_shape "shape.cpp")
add_executable(core_tensor_type "tensor_type.cpp")
add_executable(core_tensor "tensor.cpp")

utils_test_project(core_shape 3)
utils_test_project(core_tensor_type 4)
utils_test_project(core_tensor 5)