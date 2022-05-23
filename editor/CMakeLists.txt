include(FetchContent)
include(stb)
include(sdl)

add_module()
target_link_libraries(editor PUBLIC core stb SDL2 SDL2main) 