#pragma once
#include <D3D11.h>
#include <d3dx11tex.h>

class TextureClass
{
public:
	TextureClass(void);
	~TextureClass(void);
	bool Initialize(ID3D11Device* device, WCHAR* filename);
	bool Initialize(ID3D11Device* device, const char* filename);

	void Shutdown();
	void PSBindTexture(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11SamplerState* sampler);
	ID3D11ShaderResourceView*& GetTexResource();

	bool isInit()const;
private:
	bool m_initRecord;
	ID3D11ShaderResourceView *m_texture;
};
