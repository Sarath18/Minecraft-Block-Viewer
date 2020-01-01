#pragma once
#include <GL/glew.h>

class IndexBuffer {
private:
    unsigned int m_RenderID;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_count; }
};