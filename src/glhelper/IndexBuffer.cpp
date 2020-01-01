#include "IndexBuffer.h"
#include <assert.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count) {
    assert(sizeof(unsigned int) == sizeof(GLuint));
    glGenBuffers(1, &m_RenderID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RenderID);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}