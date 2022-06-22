#pragma once

#include <Voxitol/Display/Window.h>

namespace Voxitol
{
	class Application
	{
	public:
		static void Construct();
		static void Run();
		static void Close();

		static const Display::Window& GetWindow() { return *m_Window; }
	private:
		static inline Display::Window* m_Window;
		static inline bool m_IsConstructed;
		static inline bool m_IsRunning;
	};
}