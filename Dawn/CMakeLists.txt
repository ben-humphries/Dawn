##LIBRARY CONFIG
set(SRC_FILES ${SRC_FILES}
    src/Dawn/Core/Application.cpp
    src/Dawn/Core/Window.cpp
    src/Dawn/Core/Event.cpp
    src/Dawn/Core/Input.cpp
    src/Dawn/Core/Time.cpp

    src/Dawn/Render/Renderer2D.cpp
    src/Dawn/Render/Image.cpp
    src/Dawn/Render/Texture.cpp

    src/Dawn/Math/Math.cpp

    src/Dawn/ImGui/imgui_impl_opengl3.cpp

    src/Dawn/Util/Util.cpp
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

##STB##
add_subdirectory(libraries/stb)
target_link_libraries(Dawn stb)

##OPENGL##
find_package(OpenGL REQUIRED)

target_link_libraries(Dawn ${OPENGL_LIBRARIES})

##SET UP INCLUDE DIRECTORIES##
target_include_directories(Dawn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/Dawn)
