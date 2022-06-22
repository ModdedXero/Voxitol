#pragma once

namespace Voxitol::Rendering
{
	class Renderer
	{
	public:
		static void Construct();
		static void Destruct();

		static void BeginScene();
		static void EndScene();

		static void DrawCube();

	private:
		static void BeginBatch();
		static void EndBatch();
		static void Flush();
	};
}