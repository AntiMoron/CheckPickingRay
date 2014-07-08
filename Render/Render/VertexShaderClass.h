#pragma once

#include <D3D11.h>
#include <D3DX11.h>
#include <d3dx11async.h>
#include <D3Dcompiler.h>
#include <regex>
class VertexShaderClass
{
public:
	VertexShaderClass(void);
	~VertexShaderClass(void);

	HRESULT Initialize(ID3D11Device*,
		ID3D11DeviceContext*,
		WCHAR *,
		char *,
		char *,
		D3D11_INPUT_ELEMENT_DESC[],
		UINT);

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	ID3D11VertexShader *GetVertexShader();
	HRESULT SetParam(ID3D11Device* device, ID3D11DeviceContext* context, float _param[]);
	void ShutDown();

	void OutError(ID3DBlob *);
private:
	float param[8];
	ID3D11Buffer* paramBuffer;
	ID3D11VertexShader * shader;
	ID3DBlob *pBlobOutput;
	ID3D11InputLayout*  g_pVertexLayout;
};

