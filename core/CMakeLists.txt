include(FetchContent)
include(fmt)
include(spdlog)

add_module()
target_link_libraries(core PUBLIC
    fmt::fmt
    spdlog::spdlog
)

add_library(core::core ALIAS core)