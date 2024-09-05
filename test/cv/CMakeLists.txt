project(cv_sample)
project(cv_resize)

add_executable(cv_sample "sample.cpp")
add_executable(cv_resize "resize.cpp")

utils_target_link_opencv(cv_sample)
utils_target_link_opencv(cv_resize)

utils_test_project(cv_sample 0)
utils_test_project(cv_resize 1)