include(FetchContent)
include(fmt)
include(spdlog)

add_module()
target_link_libraries(core PUBLIC
    external::fmt
    external::spdlog
)

add_library(core::core ALIAS core)