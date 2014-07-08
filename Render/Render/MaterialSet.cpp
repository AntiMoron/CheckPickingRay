#include "MaterialSet.h"


MaterialSet::MaterialSet()
{
}


MaterialSet::~MaterialSet()
{
}


bool MaterialSet::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	HRESULT result;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(D3D11_SAMPLER_DESC));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	result = device->CreateSamplerState(&sampDesc, &m_samplerState);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Create SamplerState Failed!", L"", MB_OK);
		return false;
	}
	return true;
}

bool MaterialSet::Shutdown()
{
	if (m_samplerState)
	{
		m_samplerState->Release();
		m_samplerState = nullptr;
	}
	for (int i = 0; i<m_texture.size(); i++)
	{
		m_texture[i].Shutdown();
	}
	m_texture.clear();
	return true;
}

bool MaterialSet::AddTexture(ID3D11Device* device, ID3D11DeviceContext* context, const char* filename)
{
	std::cout << filename << std::endl;
	TextureClass new_node;
	m_texture.push_back(new_node);
	if (false == m_texture.back().Initialize(device, filename))
	{
		return false;
	}
	return true;
}

bool MaterialSet::UseTexture(ID3D11Device* device, ID3D11DeviceContext* context, const int index)
{
	if (m_texture[index].isInit())
		m_texture[index].PSBindTexture(device, context, m_samplerState);
	return true;
}

unsigned int MaterialSet::GetSize()
{
	return m_texture.size();
}