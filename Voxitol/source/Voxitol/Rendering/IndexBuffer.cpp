#include "vxpch.h"
#include "IndexBuffer.h"

#include <glad.h>

namespace Voxitol::Rendering
{
	IndexBuffer::IndexBuffer(size_t size)
	{
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * size, nullptr, GL_DYNAMIC_DRAW);
	}
}