#include "ConstantBuffer.h"
#include "DX12Core.h"
#include "Shader.h"
#include "Timer.h"
#include "Window.h"

#define WIDTH 1024
#define HEIGHT 1024

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	win.create("My Window", WIDTH, HEIGHT);

	DX12Core core;
	core.init(win.hwnd, WIDTH, HEIGHT);

	Shader shader;
	shader.compileShaders(&core, "ScreenSpaceTriangleVS.txt", "ScreenSpaceTrianglePS.txt");

	//PulsingTriangle pulsingTriangleCPU;
	//pulsingTriangleCPU.time = 0.f;

	LightSpinningTriangle lightSpinningTriangle;
	lightSpinningTriangle.time = 0.f;

	Timer timer;
	
	while (true) {
		// pulsingTriangleCPU.time += timer.dt();
		lightSpinningTriangle.time += timer.dt();

		for (int i = 0; i < 4; i++) {
			float angle = lightSpinningTriangle.time + (i * M_PI / 2.0f);
			lightSpinningTriangle.lights[i] = Vec4(WIDTH / 2.0f + (cosf(angle) * (WIDTH * 0.3f)), HEIGHT / 2.0f + (sinf(angle) * (HEIGHT * 0.3f)), 0, 0);
		}

		core.beginFrame();
		core.beginRenderPass();
		win.processMessages();
		if (win.keys[VK_ESCAPE] == 1) break;
		shader.draw(&core, &lightSpinningTriangle);
		core.finishFrame();
	}
	core.flushGraphicsQueue();
	return 0;
}