include(FetchContent)
include(fmt)
include(spdlog)

add_module()
target_link_libraries(core PUBLIC fmt spdlog)