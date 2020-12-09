set(SRC_FILES ${SRC_FILES}
    Main.cpp
)

add_executable(Playground ${SRC_FILES})

target_link_libraries(Playground PRIVATE Dawn)