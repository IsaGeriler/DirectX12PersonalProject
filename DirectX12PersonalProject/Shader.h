#pragma once

#include <d3dcompiler.h>
#include <fstream>
#include <sstream>

#include "DX12Core.h"
#include "PSOManager.h"
#include "ScreenSpaceTriangle.h"

class Shader {
public:
	ID3DBlob* vertexShader;
	ID3DBlob* pixelShader;

	ConstantBuffer constantBuffer;
	ScreenSpaceTriangle prim;
	PSOManager psos;

	std::string readShaderFile(std::string filename) {
		std::ifstream file(filename);
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	void compileShaders(DX12Core* core, std::string vertexShaderFile, std::string pixelShaderFile) {
		prim.init(core);
		constantBuffer.init(core, sizeof(PulsingTriangle), 2);
		ID3DBlob* status;
		std::string vertexShaderStr = readShaderFile(vertexShaderFile);
		std::string pixelShaderStr = readShaderFile(pixelShaderFile);
		
		HRESULT hr;
		hr = D3DCompile(vertexShaderStr.c_str(), strlen(vertexShaderStr.c_str()), NULL, NULL, NULL, "VS", "vs_5_0", 0, 0, &vertexShader, &status);
		hr = D3DCompile(pixelShaderStr.c_str(), strlen(pixelShaderStr.c_str()), NULL, NULL, NULL, "PS", "ps_5_0", 0, 0, &pixelShader, &status);

		if (FAILED(hr)) (char*)status->GetBufferPointer();
		psos.createPSO(core, "Triangle", vertexShader, pixelShader, prim.mesh.inputLayoutDesc);
	}

	//void draw(DX12Core* core) {
	//	core->beginRenderPass();
	//	psos.bind(core, "Triangle");
	//	prim.draw(core);
	//}

	void draw(DX12Core* core, PulsingTriangle* cb) {
		/* Bind Constant Buffer View to Root Signature index
		      Index 0 : Vertex Shader constant buffer
			  Index 1 : Pixel Shader constant buffer
		*/
		core->beginRenderPass();
		constantBuffer.update(cb, sizeof(PulsingTriangle), core->frameIndex());
		core->getCommandList()->SetGraphicsRootConstantBufferView(1, constantBuffer.getGPUAddress(core->frameIndex()));
		psos.bind(core, "Triangle");
		prim.draw(core);
	}
};