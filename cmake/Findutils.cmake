message(STATUS "cmake - version:    ${CMAKE_VERSION}")
message(STATUS "cmake - os:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "cmake - compiler:   ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER_VERSION})")
message(STATUS "")

set(is_MSVC OFF)
if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "MSVC")
    set(is_MSVC ON)
endif()

if(WIN32 OR is_MSVC)
    set(CMAKE_DEF_LINK_LIBRARY_SUFFIX ".lib")
else()
    set(CMAKE_DEF_LINK_LIBRARY_SUFFIX ".a")
endif()

# 传入静态链接库路径(不带文件后缀), 将路径替换带后缀的静态链接库路径
function(utils_def_link_library path)
    set(${path} "${${path}}${CMAKE_DEF_LINK_LIBRARY_SUFFIX}" PARENT_SCOPE)
endfunction()

# 传入项目名称，将所有静态链接库链接到项目
function(utils_target_link_all_library project)
    target_link_libraries(${project} ${OpenCV_LIBS} ${ONNXRuntime_LIBS} SRC_LIBS)
endfunction()

# 传入项目名称, 将opencv链接到项目
function(utils_target_link_opencv project)
    target_link_libraries(${project} ${OpenCV_LIBS})
endfunction()

# 传入项目名称, 将onnxruntime链接到项目
function(utils_target_link_onnxruntime project)
    target_link_libraries(${project} ${ONNXRuntime_LIBS})
endfunction()

# 传入项目名称, 将src链接到项目
function(utils_target_link_src project)
    target_link_libraries(${project} ${SRC_LIBS})
endfunction()

# 传入测试单元名称, 项目名称, 编号, 进行单元测试
function(utils_test_project test project id)
    message(STATUS "")
    message(STATUS "${id}) ${project} - test: running")
    utils_target_link_src(${project})
    add_test(${test} ${project})
    message(STATUS "${id}) ${project} - test: end")
endfunction()