#include "VertexBufferLayout.h"
#include <cassert>

VertexBufferElement::VertexBufferElement(unsigned int t, unsigned int c, bool n)
    : type(t), count(c), normalized(n)
{
}

unsigned int VertexBufferElement::GetSizeOfType(unsigned int type)
{
    switch (type)
    {
    case GL_FLOAT: return sizeof(GLfloat);
    case GL_UNSIGNED_INT: return sizeof(GLuint);
    case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
    }
    assert(false);
    return 0;
}

VertexBufferLayout::VertexBufferLayout()
    : m_stride(0)
{
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({ GL_FLOAT, count, false });
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
