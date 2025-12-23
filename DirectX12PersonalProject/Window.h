#pragma once

#define WINDOW_GET_X_LPARAM(lp)((int)(short)LOWORD(lp))
#define WINDOW_GET_Y_LPARAM(lp)((int)(short)HIWORD(lp))

#include <Windows.h>
#include <string>

class Window {
public:
	HWND hwnd;
	HINSTANCE hinstance;

	std::string name{};
	unsigned int width{};
	unsigned int height{};

	// Store key presses and mouse position
	bool keys[256];
	bool mouseButtons[3];
	int mousex;
	int mousey;

	void create(std::string window_name, unsigned int window_width, unsigned int window_height, unsigned int window_x = 0, unsigned int window_y = 0);
	void processMessages();
	void updateMouse(int x, int y);
};