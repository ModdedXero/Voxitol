#include "vxpch.h"
#include "Application.h"

#include "Time.h"

namespace Voxitol
{
	void Application::Construct()
	{
		if (m_IsConstructed) return;

		m_Window = new Display::Window({ 1280, 720 });
		m_IsRunning = false;
		m_IsConstructed = true;

		Time::Construct();
	}

	void Application::Run()
	{
		m_IsRunning = true;

		while (m_IsRunning)
		{
			Time::CalculateTime();

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_IsRunning = false;
		m_Window->OnDestroy();
	}
}