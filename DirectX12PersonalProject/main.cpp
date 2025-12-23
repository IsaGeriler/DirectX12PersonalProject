#include "DX12Core.h"
#include "Window.h"

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	win.create("My Window", 1024, 1024);

	DX12Core core;
	core.init(win.hwnd, 1024, 1024);
	
	while (true) {
		core.beginFrame();
		win.processMessages();
		if (win.keys[VK_ESCAPE] == 1) break;
		core.finishFrame();
	}
	core.flushGraphicsQueue();
	return 0;
}