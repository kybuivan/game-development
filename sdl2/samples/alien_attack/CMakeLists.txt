add_executable(alien_attack main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(alien_attack PRIVATE core editor)
add_custom_command(TARGET alien_attack POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:alien_attack>/assets/)