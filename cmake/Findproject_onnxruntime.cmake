if(DEFINED ENV{ONNXRUNTIME_DIR})
    set(ONNXRuntime_DIR $ENV{ONNXRUNTIME_DIR})
else()
    message(FATAL_ERROR
            "Environment variables 'ONNXRUNTIME_DIR' are not defined. "
            "Please define the environment variable 'ONNXRUNTIME_DIR' correctly and try compiling again. "
    )
endif()

set(ONNXRuntime_INCLUDE     "${ONNXRuntime_DIR}/include")
set(ONNXRuntime_LIBS        "${ONNXRuntime_DIR}/lib/onnxruntime")

utils_def_link_library(ONNXRuntime_LIBS)

message(STATUS " ")
message(STATUS "2) ONNXRuntime - dir:       ${ONNXRuntime_DIR}")
message(STATUS "2) ONNXRuntime - include:   ${ONNXRuntime_INCLUDE}")
message(STATUS "2) ONNXRuntime - lib:       ${ONNXRuntime_LIBS}")

include_directories(${ONNXRuntime_INCLUDE})
target_link_libraries(${PROJECT_NAME} ${ONNXRuntime_LIBS})
