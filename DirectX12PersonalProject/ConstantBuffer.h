#pragma once

#include "DX12Core.h"
#include "MyMath.h"

struct alignas(16) PulsingTriangle {
	float time;
};

struct alignas(16) LightSpinningTriangle {
	float time;
	float padding[3];
	Vec4 lights[4];
};

class ConstantBuffer {
public:
	// CPU Memory & Size
	ID3D12Resource* constantBuffer;
	unsigned char* buffer;
	unsigned int cbSizeInBytes;

	void init(DX12Core* core, unsigned int sizeInBytes, int frames) {
		cbSizeInBytes = (sizeInBytes + 255) & ~255;
		HRESULT hr;
		D3D12_HEAP_PROPERTIES heapprops = {};
		heapprops.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprops.CreationNodeMask = 1;
		heapprops.VisibleNodeMask = 1;
		D3D12_RESOURCE_DESC cbDesc = {};
		cbDesc.Width = cbSizeInBytes * frames;
		cbDesc.Height = 1;
		cbDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbDesc.DepthOrArraySize = 1;
		cbDesc.MipLevels = 1;
		cbDesc.SampleDesc.Count = 1;
		cbDesc.SampleDesc.Quality = 0;
		cbDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		hr = core->device->CreateCommittedResource(&heapprops, D3D12_HEAP_FLAG_NONE, &cbDesc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, __uuidof(ID3D12Resource), (void**)&constantBuffer);
		hr = constantBuffer->Map(0, NULL, (void**)&buffer);
	}

	// Update via a memcpy
	void update(void* data, unsigned int sizeInBytes, int frame) {
		memcpy(buffer + (frame * cbSizeInBytes), data, sizeInBytes);
	}
	
	// GPU address of contents
	D3D12_GPU_VIRTUAL_ADDRESS getGPUAddress(int frame) {
		return (constantBuffer->GetGPUVirtualAddress() + (frame * cbSizeInBytes));
	}
};