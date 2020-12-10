set(SRC_FILES ${SRC_FILES}
    Main.cpp

    Core/DawnEditor.cpp

    Panels/SceneHierarchyPanel.cpp
    Panels/InspectorPanel.cpp
)

add_executable(DawnEditor ${SRC_FILES})

target_include_directories(DawnEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/Dawn/include)

target_link_libraries(DawnEditor PRIVATE Dawn)

