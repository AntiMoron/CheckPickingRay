#pragma once
#include<D3D11.h>
#include<D3DX11.h>
#include<D3DX10math.h>
#include<stdio.h>
#include"VertexClass.h"


class RayRenderClass
{
public:
	RayRenderClass();
	~RayRenderClass();

	HRESULT Initialize(ID3D11Device*& device, ID3D11DeviceContext*& context);
	HRESULT Shutdown();

	HRESULT Render(ID3D11Device*& device, ID3D11DeviceContext*& context);

	HRESULT UpdateStartPosition(D3DXVECTOR3 st);
	HRESULT UpdateEndPosition(D3DXVECTOR3 ed);

	D3DXVECTOR3 GetStartPosition();
	D3DXVECTOR3 GetEndPosition();

	void SetColor(float r, float g, float b, float a);
private:
	D3DXVECTOR4 m_color;
	ID3D11Buffer* m_outlineColor;
	VertexClass pts[2];
	ID3D11Buffer* m_vertices;
};


