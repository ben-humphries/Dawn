#include "Dawn/Application.h"

#include <iostream>

GLFWwindow* Application::window;

void Application::Init()
{
  glfwInit();

  // Create GLFW Window
  window = glfwCreateWindow(800, 600, "Dawn Engine App", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return;
  }
  int test = 5;
  glViewport(0, 0, 800, 600);
}

void Application::Start()
{
  // Main Event Loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 0.7, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Application::Close() { glfwTerminate(); }