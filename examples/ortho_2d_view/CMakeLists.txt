add_executable(ortho_2d_view)

target_sources(ortho_2d_view PRIVATE main.cpp)

target_include_directories(ortho_2d_view PRIVATE
    "${PROJECT_SOURCE_DIR}/examples/images"
    "${PROJECT_SOURCE_DIR}/examples/shaders"
)

target_link_libraries(ortho_2d_view PRIVATE jhoyt::mf)
