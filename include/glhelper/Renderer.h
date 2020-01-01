#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"


void GLClearError();
void GLCheckError();

class Renderer {
public:
    void Draw(const unsigned int& vao, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};