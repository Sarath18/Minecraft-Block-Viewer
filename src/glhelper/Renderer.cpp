#include "Renderer.h"
#include <iostream>

void Renderer::Clear() const {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const unsigned int& vao, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    glBindVertexArray(vao);
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}