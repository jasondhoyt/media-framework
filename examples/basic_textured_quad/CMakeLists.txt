add_executable(basic_textured_quad)

target_sources(basic_textured_quad PRIVATE main.cpp)

target_include_directories(basic_textured_quad PRIVATE
    "${PROJECT_SOURCE_DIR}/examples/images"
    "${PROJECT_SOURCE_DIR}/examples/shaders"
)

target_link_libraries(basic_textured_quad PRIVATE jhoyt::mf)
