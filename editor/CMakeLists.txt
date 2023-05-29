include(FetchContent)
include(stb)
include(sdl)
include(tinyxml2)
include(openal)
include(sndfile)

add_module()
target_link_libraries(editor PUBLIC
    core::core
    stb::stb
    SDL2::SDL2
    SDL2::SDL2main
    tinyxml2::tinyxml2
    OpenAL::OpenAL
    sndfile::sndfile
) 