#include "Window.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	win.create("My Window", 1024, 1024);
	
	while (true) {
		win.processMessages();
	}
}