#include "vxpch.h"
#include "Window.h"

namespace Voxitol::Display
{
	Window::Window(const WindowsSpecs& specs)
		: m_Window(nullptr)
	{
		m_Specs.width = specs.width;
		m_Specs.height = specs.height;

		if (!glfwInit())
		{
			// Assert error
			return;
		}

		m_Window = glfwCreateWindow(specs.width, specs.height, "Voxitol", NULL, NULL);
		if (!m_Window)
		{
			// Assert error
			return;
		}

		glfwMakeContextCurrent(m_Window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(m_Window, &m_Specs);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();

		glClearColor(0.4f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_Window);
	}

	void Window::OnDestroy()
	{
		glfwTerminate();
	}
}