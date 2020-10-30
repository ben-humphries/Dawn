#pragma once

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Application
{
 public:
  static void Init();

  // Enters infinite event loop
  static void Start();

  static void Close();

 private:
  static GLFWwindow* window;
};