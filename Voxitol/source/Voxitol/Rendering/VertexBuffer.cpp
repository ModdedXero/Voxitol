#include "vxpch.h"
#include "VertexBuffer.h"

namespace Voxitol::Rendering
{
	VertexBuffer::VertexBuffer(size_t size)
	{
		m_Buffer = new Vertex[size];
		m_BufferPtr = m_Buffer;

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexArrayAttrib(m_VAO, 0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, transform));

		glEnableVertexArrayAttrib(m_VAO, 1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

		glEnableVertexArrayAttrib(m_VAO, 2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));

		glEnableVertexArrayAttrib(m_VAO, 3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texID));
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

		delete[] m_Buffer;
		delete[] m_BufferPtr;
	}

	void VertexBuffer::Clear()
	{
		m_BufferPtr = m_Buffer;
	}

	GLsizeiptr VertexBuffer::Size() const
	{
		return (uint8_t*)m_BufferPtr - (uint8_t*)m_Buffer;
	}
}