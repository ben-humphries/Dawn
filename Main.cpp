#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"

int main() {



    glfwInit();

    //Create GLFW Window
    GLFWwindow * window = glfwCreateWindow(800, 600, "Dawn Engine App", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    //Main Event Loop
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}