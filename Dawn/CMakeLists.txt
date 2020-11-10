##LIBRARY CONFIG
set(SRC_FILES ${SRC_FILES}
    src/Application.cpp
    src/Window.cpp
    src/Event.cpp
    src/Input.cpp
)

add_library(Dawn ${SRC_FILES})

##GLFW##
add_subdirectory(libraries/glfw)
target_link_libraries(Dawn glfw)

##GLAD##
add_subdirectory(libraries/glad)
target_link_libraries(Dawn glad)

##OPENGL##
find_package(OpenGL REQUIRED)

target_link_libraries(Dawn ${OPENGL_LIBRARIES})

##SET UP INCLUDE DIRECTORIES##
target_include_directories(Dawn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS})
