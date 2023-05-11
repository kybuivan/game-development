include(FetchContent)
include(stb)
include(sdl)
include(tinyxml2)
include(openal)
include(sndfile)

add_module()
target_link_libraries(editor PUBLIC core stb SDL2-static SDL2main tinyxml2 OpenAL sndfile) 