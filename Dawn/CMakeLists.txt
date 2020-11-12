##LIBRARY CONFIG
set(SRC_FILES ${SRC_FILES}
    src/Dawn/Core/Application.cpp
    src/Dawn/Core/Window.cpp
    src/Dawn/Core/Event.cpp
    src/Dawn/Core/Input.cpp

    src/Dawn/ImGui/imgui_impl_glfw.cpp
    src/Dawn/ImGui/imgui_impl_opengl3.cpp
)

add_library(Dawn ${SRC_FILES})

##GLFW##
add_subdirectory(libraries/glfw)
target_link_libraries(Dawn glfw)

##GLAD##
add_subdirectory(libraries/glad)
target_link_libraries(Dawn glad)

##IMGUI##
add_subdirectory(libraries/imgui)
target_link_libraries(Dawn ImGui)

##OPENGL##
find_package(OpenGL REQUIRED)

target_link_libraries(Dawn ${OPENGL_LIBRARIES})

##SET UP INCLUDE DIRECTORIES##
target_include_directories(Dawn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)
