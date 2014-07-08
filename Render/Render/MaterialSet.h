#pragma once
#include<vector>
#include<D3D11.h>
#include<D3DX11.h>
#include<iostream>
#include"TextureClass.h"

class MaterialSet
{
public:
	MaterialSet();
	~MaterialSet();
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context);
	bool AddTexture(ID3D11Device* device, ID3D11DeviceContext* context, const char* filename);
	bool UseTexture(ID3D11Device* device, ID3D11DeviceContext* context, const int index);
	bool Shutdown();

	unsigned int GetSize();
private:
	ID3D11SamplerState* m_samplerState;
	std::vector<TextureClass> m_texture;
};

