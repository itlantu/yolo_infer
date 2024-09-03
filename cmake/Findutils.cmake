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

function(DEF_LINK_LIBRARY path)
    set(${path} "${${path}}${CMAKE_DEF_LINK_LIBRARY_SUFFIX}" PARENT_SCOPE)
endfunction()