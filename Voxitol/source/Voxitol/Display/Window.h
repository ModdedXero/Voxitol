#pragma once

#include <glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Voxitol::Display
{
	struct WindowsSpecs
	{
		uint32_t width = 0;
		uint32_t height = 0;
	};

	class Window
	{
	public:
		Window(const WindowsSpecs& specs = WindowsSpecs());

		void OnUpdate();
		void OnDestroy();

		bool IsRunning() const { return !glfwWindowShouldClose(m_Window); }

		uint32_t GetWidth() const { return m_Specs.width; }
		uint32_t GetHeight() const { return m_Specs.height; }

		GLFWwindow* GetNativeWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window;
		WindowsSpecs m_Specs;
	};
}