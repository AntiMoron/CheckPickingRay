#include "TextureClass.h"


TextureClass::TextureClass(void)
{
	m_texture = NULL;
	m_initRecord = false;
}


TextureClass::~TextureClass(void)
{
}

bool TextureClass::Initialize(ID3D11Device* device, const char* filename)
{
	HRESULT result;
	m_initRecord = false;
	result = D3DX11CreateShaderResourceViewFromFileA(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
	{
		MessageBoxA(NULL, "CreateShaderResource Failed!", filename, MB_OK);
		return false;
	}
	m_initRecord = true;
	return true;
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR *filename)
{
	HRESULT result;
	m_initRecord = false;
	;
	m_initRecord = true;
	/*D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc,sizeof(D3D11_SAMPLER_DESC));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	result = device->CreateSamplerState(&sampDesc,&m_SamplerState);
	if(FAILED(result))
	{
	MessageBox(NULL,L"Create SamplerState Failed!",filename,MB_OK);
	return false;
	}*/
	return true;
}

void TextureClass::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}
}

ID3D11ShaderResourceView*& TextureClass::GetTexResource()
{
	return m_texture;
}


void TextureClass::PSBindTexture(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11SamplerState* sampler)
{
	context->PSSetShaderResources(0, 1, &m_texture);
	context->PSSetSamplers(0, 1, &sampler);
}

bool TextureClass::isInit()const
{
	return m_initRecord;
}