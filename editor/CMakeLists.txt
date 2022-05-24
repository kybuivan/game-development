include(FetchContent)
include(stb)
include(sdl)
include(tinyxml2)

add_module()
target_link_libraries(editor PUBLIC core stb SDL2 SDL2main tinyxml2) 