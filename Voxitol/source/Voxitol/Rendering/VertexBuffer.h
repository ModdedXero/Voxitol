#pragma once

#include "glad.h"
#include "glm/glm.hpp"

namespace Voxitol::Rendering
{
	struct Vertex
	{
	public:
		glm::vec3 transform;
		glm::vec4 color;
		glm::vec2 texCoords;
		float texID;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() {}
		VertexBuffer(size_t size);
		~VertexBuffer();

		void Clear();

		GLsizeiptr Size() const;

	private:
		Vertex* m_Buffer;
		Vertex* m_BufferPtr;

		uint32_t m_VAO;
		uint32_t m_VBO;
	};
}