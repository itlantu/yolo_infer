add_library(SRC_LIBS STATIC
#        "preprocess.cpp"
        "core/tensor.cpp"
        "core/shape.cpp"
)

target_link_libraries(${PROJECT_NAME} SRC_LIBS)