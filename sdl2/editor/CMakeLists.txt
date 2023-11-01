include(FetchContent)
include(stb)
include(sdl2)
include(tinyxml2)
include(openal)
include(sndfile)

add_module()
target_link_libraries(editor PUBLIC
    core::core
    external::stb
    external::sdl2
    external::sdl2main
    external::tinyxml2
    external::openal
    external::sndfile
) 