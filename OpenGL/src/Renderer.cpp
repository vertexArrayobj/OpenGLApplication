#include "GLErrorManager.h"
#include "Renderer.h"
#include<iostream>



void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::SetClearColor(const float v1, const float v2, const float v3, const float v4)
{
	GLCall(glClearColor(v1, v2, v3, v4));
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
