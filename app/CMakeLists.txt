add_executable(app main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(app PRIVATE core editor)

add_custom_command(TARGET app POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:app>/assets/)