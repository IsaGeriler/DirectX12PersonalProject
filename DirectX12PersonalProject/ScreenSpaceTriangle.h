#pragma once

#include "Mesh.h"
#include "MyMath.h"

struct PRIM_VERTEX {
	Vec3 position;
	Colour colour;
};

class ScreenSpaceTriangle{
public:
	PRIM_VERTEX vertices[3];
	Mesh mesh;

	void init(DX12Core* core) {
		vertices[0].position = Vec3(0, 1.0f, 0);
		vertices[0].colour = Colour(0, 1.0f, 0);
		vertices[1].position = Vec3(-1.0f, -1.0f, 0);
		vertices[1].colour = Colour(1.0f, 0, 0);
		vertices[2].position = Vec3(1.0f, -1.0f, 0);
		vertices[2].colour = Colour(0, 0, 1.0f);
		mesh.init(core, &vertices[0], sizeof(PRIM_VERTEX), 3);
	}

	void draw(DX12Core* core) {
		mesh.draw(core);
	}
};