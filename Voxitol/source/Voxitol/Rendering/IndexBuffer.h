#pragma once

namespace Voxitol::Rendering
{
	class IndexBuffer
	{
	public:
		IndexBuffer() {}
		IndexBuffer(size_t size);
		
	private:
		uint32_t m_IBO;
		uint32_t m_IndexOffset = 0;
		std::vector<uint32_t> m_IndexBuffer;
	};
}