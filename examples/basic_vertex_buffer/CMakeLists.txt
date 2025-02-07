add_executable(basic_vertex_buffer)

target_sources(basic_vertex_buffer PRIVATE main.cpp)

target_include_directories(basic_vertex_buffer PRIVATE "${PROJECT_SOURCE_DIR}/examples/shaders")

target_link_libraries(basic_vertex_buffer PRIVATE jhoyt::mf)
