#pragma once

#include <chrono>

namespace Voxitol
{
	const float FixedUpdateInterval = 0.2f;

	class Time
	{
		typedef std::chrono::high_resolution_clock TimeClock;
		typedef std::chrono::steady_clock::time_point TimeSnapshot;
		typedef std::chrono::duration<float> FSeconds;

		friend class Application;
	public:
		static float GetSeconds() { return m_Time; }
		static float GetMilliseconds() { return m_Time * 1000; }
		static float GetDeltaTime() { return m_DeltaTime * m_TimeScale; }
		static float GetFPS() { return 1 / m_DeltaTime; }
		static float GetFixedDeltaTime() { return FixedUpdateInterval * m_TimeScale; }

		static void SetTimeScale(float scale) { m_TimeScale = scale; }

	private:
		static inline float m_Time = 0.0f;
		static inline float m_DeltaTime = 0.0f;
		static inline float m_TimeScale = 1.0f;

		static inline TimeSnapshot m_StartTime;
		static inline TimeSnapshot m_LastFrameTime;
		static inline TimeSnapshot m_FixedLoop;

	private:
		static inline void Construct()
		{
			m_StartTime = TimeClock::now();
		}

		static inline void CalculateTime()
		{
			TimeSnapshot current = TimeClock::now();
			FSeconds fsecs = current - m_StartTime;
			FSeconds dsecs = current - m_LastFrameTime;

			if (dsecs.count() > 10.0f)
			{
				m_Time = 0.0f;
				m_DeltaTime = 0.0f;
			}
			else
			{
				m_Time = fsecs.count();
				m_DeltaTime = dsecs.count();
			}

			m_LastFrameTime = current;
		}
	};
}