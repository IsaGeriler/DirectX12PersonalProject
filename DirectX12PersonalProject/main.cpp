#include "DX12Core.h"
#include "Shader.h"
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
	
	while (true) {
		core.beginFrame();
		core.beginRenderPass();
		win.processMessages();
		if (win.keys[VK_ESCAPE] == 1) break;
		shader.draw(&core);
		core.finishFrame();
	}
	core.flushGraphicsQueue();
	return 0;
}