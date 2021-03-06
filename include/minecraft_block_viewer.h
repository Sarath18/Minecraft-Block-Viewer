//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
#pragma once

// General Libraries
#include <iostream>

// OpenGL Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// OpenGL Helper Libraries
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"


#include "Block.h"
#include <fstream>

void GLClearError() {
  while(glGetError() != GL_NO_ERROR);
}

void GLCheckError() {
  while(GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << ": " << gluErrorString(error) << ")" << std::endl;
  }
}

bool is_block_translucent(std::basic_string<char> &block_name);
bool update_specular_texture(std::vector<float> &texture_coordinates, Json::Value root, const std::string& block_name);
bool update_break_texture(std::vector<float> &texture_coordinates, const int state);

const int WIDTH = 450, HEIGHT = 550;
int SCREEN_WIDTH, SCREEN_HEIGHT;

