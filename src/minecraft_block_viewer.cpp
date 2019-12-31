//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
// General Libraries
#include <iostream>

// OpenGL Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int WIDTH = 550, HEIGHT = 700;
int SCREEN_WIDTH, SCREEN_HEIGHT;

int main() {
  std::cout << "Welcome to Minecraft Block Viewer" << std::endl;

  glewExperimental = true;

  // Initialize GLFW
  if(!glfwInit()) {
    std::cout << stderr << "Failed to initialize GLFW.\n";
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create Window
  GLFWwindow *window;
  window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft Block Viewer", NULL, NULL);
  if(window == NULL) {
    std::cout << stderr << "Failed to openg GLFW window. If youhave an Intel GPU, they are not 3.3 compatible.\n";
    getchar();
    glfwTerminate();
    return -1;
  }

  glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

  glfwMakeContextCurrent(window);

  // Peripheral Input Configuration
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Set background color
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    do {
      glClear(GL_COLOR_BUFFER_BIT);

      // Swap Buffers
      glfwSwapBuffers(window);
      glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
  }

  return 0;
}
