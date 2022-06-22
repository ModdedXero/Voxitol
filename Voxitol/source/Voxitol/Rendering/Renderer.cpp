#include "vxpch.h"
#include "Renderer.h"

#include "Shader.h"
#include "IndexBuffer.h"
#include "Framebuffer.h"
#include "VertexBuffer.h"

#include <Voxitol/Core/Application.h>

#include <glad.h>

namespace Voxitol::Rendering
{
	static const size_t MaxVertexCount = 500;
	static const size_t MaxTextureCount = 32;

	struct RenderData
	{
		VertexBuffer VertexBuffer;
		IndexBuffer IndexBuffer;

		uint32_t SVAO = 0;
		uint32_t SVBO = 0;

		Shader ScreenShader;

		std::array<uint32_t, MaxTextureCount> TextureSlots;
		uint32_t TextureSlotIndex = 1;
		uint32_t WhiteTexture = 0;

		Framebuffer Framebuffer;

	} static s_Data;

	void Renderer::Construct()
	{
		// Buffers

		s_Data.VertexBuffer = VertexBuffer(MaxVertexCount);
		s_Data.IndexBuffer = IndexBuffer(MaxVertexCount);

		// Framebuffer

		FramebufferSpecification fbSpec;
		fbSpec.Attachments =
		{
			FramebufferTextureFormat::RGBA8,
			FramebufferTextureFormat::RED_INTEGER,
			FramebufferTextureFormat::Depth
		};
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		s_Data.Framebuffer = Framebuffer(fbSpec);

		float quadVertices[] = 
		{
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		glGenVertexArrays(1, &s_Data.SVAO);
		glGenBuffers(1, &s_Data.SVBO);
		glBindVertexArray(s_Data.SVAO);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.SVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		s_Data.ScreenShader = Shader(Application::GetResourcesPath() / "/Shader/ScreenShader.glsl");
		s_Data.ScreenShader.SetInteger("screenTexture", 0);

		// Setup default texture

		glCreateTextures(GL_TEXTURE_2D, 1, &s_Data.WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, s_Data.WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		uint32_t color = 0xffffffff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		for (size_t i = 1; i < MaxTextureCount; i++)
			s_Data.TextureSlots[i] = 0;

		// OpenGL Settings
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::Destruct()
	{
		glDeleteVertexArrays(1, &s_Data.m_VAO);
		glDeleteVertexArrays(1, &s_Data.SVAO);
		glDeleteBuffers(1, &s_Data.SVBO);
		glDeleteBuffers(1, &s_Data.m_VBO);
		glDeleteBuffers(1, &s_Data.IBO);

		delete[] s_Data.VertexBuffer;
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::DrawCube()
	{
	}

	void Renderer::BeginBatch()
	{
	}

	void Renderer::EndBatch()
	{
	}

	void Renderer::Flush()
	{
	}
}