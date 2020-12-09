set(SRC_FILES ${SRC_FILES}
    Main.cpp

    Core/DawnEditor.cpp
)

add_executable(DawnEditor ${SRC_FILES})

target_link_libraries(DawnEditor PRIVATE Dawn)