add_library(SRC_LIBS STATIC
#        "preprocessing.cpp"
#        "core/tensor.cpp"
        "core/shape.cpp"
)

target_link_libraries(${PROJECT_NAME} SRC_LIBS)