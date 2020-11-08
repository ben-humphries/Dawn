##LIBRARY CONFIG
set(SRC_FILES ${SRC_FILES}
    src/Application.cpp
    src/Window.cpp
    src/Event.cpp
    src/Input.cpp
)

add_library(Dawn ${SRC_FILES})

##GLFW##
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libraries/glfw-3.3.2/lib/libglfw3.a)
set_target_properties(glfw PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/libraries/glfw-3.3.2/include)

target_link_libraries(Dawn glfw)

##GLEW##
add_library(glew STATIC IMPORTED GLOBAL)
set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew-2.1.0/lib/Release/x64/glew32s.lib)
set_target_properties(glew PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew-2.1.0/include)

target_link_libraries(Dawn glew)

##OPENGL##
find_package(OpenGL REQUIRED)

target_link_libraries(Dawn ${OPENGL_LIBRARIES})

##SET UP INCLUDE DIRECTORIES##
target_include_directories(Dawn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS})
