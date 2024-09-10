message(STATUS "cmake - version:    ${CMAKE_VERSION}")
message(STATUS "cmake - os:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "cmake - compiler:   ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER_VERSION})")
message(STATUS "")

set(test_id 0)
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
    target_link_libraries(${project} SRC_LIBS)
endfunction()

# 传入原始字符和对齐长度，生成左对齐
function(utils_set_align_string output str num)
    string(LENGTH "${str}" length)
    set(space "")
    # 插入空格
    while(${num} GREATER ${length})
        string(APPEND space " ")
        math(EXPR length "${length} + 1")
        set(length  ${length} PARENT_SCOPE)
        set(space   ${space} PARENT_SCOPE)
    endwhile()
    set(${output} "${str}${space}" PARENT_SCOPE)
endfunction()

# 传入测试项目名称, 进行单元测试
function(utils_test_project _project)
    math(EXPR id "${test_id} + 1")
    set(test_id ${id} PARENT_SCOPE)

    utils_set_align_string(test_name    "${_project}" 25)

    message(STATUS "test${id}: \t ${test_name} - build")
    add_test("test_${_project}" ${_project})
endfunction()

# 传入测试项目名称, 测试文件路径, 库名称, 生成对应名称的project并且根据文件路径生成可执行文件，再链接库
# example:
#   set(links "opencv" "onnxruntime")
#   _utils_add_test_code _project("cv_resize" ${CMAKE_CURRENT_SOURCE_DIR}/cv/resize.cpp} ${links})
function(utils_add_test_code _project _path _link)
    project("${_project}")
    add_executable(${_project} ${_path})

    foreach(library ${_link})
        if("${_link}" STREQUAL "opencv")
            utils_target_link_opencv("${_project}")
        elseif("${_link}" STREQUAL "onnxruntime")
            utils_target_link_onnxruntime("${_project}")
        elseif("${_link}" STREQUAL "src")
            utils_target_link_src("${_project}")
        else()
            message(FATAL_ERROR "unknown link library: ${library}")
        endif()
    endforeach()
    set(test_id ${test_id})
    utils_test_project("${_project}")
    set(test_id ${test_id} PARENT_SCOPE)
endfunction()

# 传入测试项目名称, 测试文件路径, LINK, 库名称， 辅助调用_utils_add_test_code函数
# example:
#   utils_add_test_file("${CMAKE_CURRENT_SOURCE_DIR}/cv/resize.cpp}" LINK OpenCV)
macro(utils_add_test_file _path)
    set(_link)
    # 得到_project
    # 去掉.../test/
    string(REGEX REPLACE "[A-Za-z_:/\\]*test/" "" _project ${_path})
    # 去掉.cpp
    string(REGEX REPLACE ".cpp" "" _project ${_project})
    # 替换'/'为'_'
    string(REGEX REPLACE "/" "_" _project ${_project})

    foreach (library ${ARGN})
        # 转小写
        string(TOLOWER "${library}" library)
        if("${library}" STREQUAL "link")
            continue()
        endif()
        list(APPEND _link "${library}")
    endforeach()
    utils_add_test_code(${_project} ${_path} ${_link})
endmacro()