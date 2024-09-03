if(DEFINED ENV{OpenCV_DIR})
    set(OpenCV_DIR "$ENV{OpenCV_DIR}")
elseif(DEFINED ENV{OpenCV_HOME})
    set(OpenCV_DIR "${OpenCV_HOME}")
    message(WARNING
            "You have not defined the environment variable 'OpenCV_DIR'. "
            "The program will attempt to use the 'OpenCV_HOME' environment variable. "
            "'OpenCV_HOME' = '$ENV{OpenCL_HOME}'"
    )
else()
    # 未定义OpenCV_DIR或OpenCV_HOME
    message(FATAL_ERROR
            "Environment variables 'OpenCV_DIR' or 'OpenCV_HOME' are not defined. "
            "Please define the environment variable 'OpenCV_DIR' correctly and try compiling again. "
    )
endif()


set(CMAKE_PREFIX_PATH "${OpenCV_DIR}")
find_package(OpenCV)

if({OpenCV_FOUND} EQUAL 0)
    # 未找到OpenCV
    message(FATAL_ERROR
        "attempt to load OpenCV failed."
        "please redefine the correct environment 'OpenCV_DIR'. \n"
        "note: \n"
        "ENV OpenCV_DIR     = '$ENV{OpenCV_DIR}' "
        "ENV OpenCV_HOME    = '$ENV{OpenCV_HOME}' "
    )
endif()

message(STATUS " ")
message(STATUS "1) OpenCV - dir:           ${OpenCV_DIR}")
message(STATUS "1) OpenCV - version        ${OpenCV_VERSION}")
message(STATUS "1) OpenCV - include:       ${OpenCV_INCLUDE_DIRS}")
message(STATUS "1) OpenCV - lib:           ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})