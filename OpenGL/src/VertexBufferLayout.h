#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    bool normalized;

    VertexBufferElement(unsigned int t, unsigned int c, bool n);

    static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_stride;

public:
    VertexBufferLayout();

    template<typename T>
    void Push(unsigned int count)
    {
        static_assert(std::false_type::value, "Unsupported type");
    }

    template<>
    void Push<float>(unsigned int count);

    template<>
    void Push<unsigned int>(unsigned int count);

    template<>
    void Push<unsigned char>(unsigned int count);

    inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_stride; }
};
