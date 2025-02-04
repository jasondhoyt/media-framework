add_executable(basic_window)

target_sources(basic_window PRIVATE main.cpp)

target_link_libraries(basic_window PRIVATE jhoyt::mf)
