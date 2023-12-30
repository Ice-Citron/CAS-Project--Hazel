#pragma once


namespace Hazel {

	class GraphicsContext {
	// This class will be an interface, which will be inherited by specific RenderAPIs, such as Vulkan, OpenGL, DirectX, Metal, etc.
	public:

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;


	};
}
