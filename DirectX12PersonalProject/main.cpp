#include "ConstantBuffer.h"
#include "DX12Core.h"
#include "Shader.h"
#include "Timer.h"
#include "Window.h"

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	win.create("My Window", 1024, 1024);

	DX12Core core;
	core.init(win.hwnd, 1024, 1024);

	Shader shader;
	shader.compileShaders(&core, "ScreenSpaceTriangleVS.txt", "ScreenSpaceTrianglePS.txt");

	PulsingTriangle pulsingTriangleCPU;
	pulsingTriangleCPU.time = 0.f;

	Timer timer;
	
	while (true) {
		pulsingTriangleCPU.time += timer.dt();

		core.beginFrame();
		core.beginRenderPass();
		win.processMessages();
		if (win.keys[VK_ESCAPE] == 1) break;
		shader.draw(&core, &pulsingTriangleCPU);
		core.finishFrame();
	}
	core.flushGraphicsQueue();
	return 0;
}