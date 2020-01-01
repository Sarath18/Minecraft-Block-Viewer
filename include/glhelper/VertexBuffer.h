#pragma once
#include <GL/glew.h>

class VertexBuffer {
private:
    unsigned int m_RenderID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void UpdateData(const void* data, unsigned int size) const;
    void Bind() const;
    void Unbind() const;
};