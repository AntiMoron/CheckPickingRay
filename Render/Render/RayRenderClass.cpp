#include "RayRenderClass.h"

RayRenderClass::RayRenderClass()
{
	ZeroMemory(pts, sizeof(pts));
	//start point
	pts[0].pos[0] = 0.0f;
	pts[0].pos[1] = 0.0f;
	pts[0].pos[2] = 0.0f;
	pts[0].pos[3] = 1.0f;

	pts[0].col[0] = 1.0f;
	pts[0].col[1] = 1.0f;
	pts[0].col[2] = 1.0f;
	pts[0].col[3] = 1.0f;
	//end point
	pts[1].pos[0] = 1.0f;
	pts[1].pos[1] = 0.0f;
	pts[1].pos[2] = 0.0f;
	pts[1].pos[3] = 1.0f;

	pts[1].col[0] = 1.0f;
	pts[1].col[1] = 1.0f;
	pts[1].col[2] = 1.0f;
	pts[1].col[3] = 1.0f;

	m_color.x = 1.0f;
	m_color.y = 1.0f;
	m_color.z = 1.0f;
	m_color.w = 1.0f;
}


RayRenderClass::~RayRenderClass()
{
}

HRESULT RayRenderClass::Initialize(ID3D11Device*& device, ID3D11DeviceContext*& context)
{
	HRESULT hr = E_FAIL;
	D3D11_BUFFER_DESC verticesDesc;
	D3D11_SUBRESOURCE_DATA verticesData;
	ZeroMemory(&verticesDesc, sizeof(verticesDesc));
	verticesDesc.Usage = D3D11_USAGE_DYNAMIC;
	verticesDesc.ByteWidth = sizeof(VertexClass)* 2;
	verticesDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	verticesDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	ZeroMemory(&verticesData, sizeof(verticesData));
	verticesData.pSysMem = &pts[0].pos[0];
	hr = device->CreateBuffer(&verticesDesc, &verticesData, &m_vertices);
	if (FAILED(hr))
	{
		return hr;
	}

	D3D11_BUFFER_DESC colorDesc;
	D3D11_MAPPED_SUBRESOURCE myresource;
	D3DXVECTOR4* dptr;
	ZeroMemory(&colorDesc, sizeof(colorDesc));
	colorDesc.Usage = D3D11_USAGE_DYNAMIC;
	colorDesc.ByteWidth = sizeof(float)* 4;
	colorDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	colorDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = device->CreateBuffer(&colorDesc, NULL, &m_outlineColor);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = context->Map(m_outlineColor, 0, D3D11_MAP_WRITE_DISCARD, 0, &myresource);
	if (FAILED(hr))
	{
		return hr;
	}
	dptr = (D3DXVECTOR4*)myresource.pData;
	*dptr = m_color;
	context->Unmap(m_outlineColor, 0);
	context->PSSetConstantBuffers(0, 1, &m_outlineColor);
	return S_OK;
}

HRESULT RayRenderClass::Shutdown()
{
	if (m_vertices != nullptr)
	{
		m_vertices->Release();
		m_vertices = nullptr;
	}
	return S_OK;
}

HRESULT RayRenderClass::UpdateStartPosition(D3DXVECTOR3 st)
{
	HRESULT hr = S_OK;
	pts[0].pos[0] = st.x;
	pts[0].pos[1] = st.y;
	pts[0].pos[2] = st.z;
	return hr;
}

HRESULT RayRenderClass::UpdateEndPosition(D3DXVECTOR3 ed)
{
	HRESULT hr = S_OK;

	pts[1].pos[0] = ed.x;
	pts[1].pos[1] = ed.y;
	pts[1].pos[2] = ed.z;
	return hr;
}

D3DXVECTOR3 RayRenderClass::GetStartPosition()
{
	D3DXVECTOR3 ret = { pts[0].pos };
	return ret;
}

D3DXVECTOR3 RayRenderClass::GetEndPosition()
{
	D3DXVECTOR3 ret = { pts[1].pos };
	return ret;
}

HRESULT RayRenderClass::Render(ID3D11Device*& device, ID3D11DeviceContext*& context)
{
	HRESULT hr = E_FAIL;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D11_MAPPED_SUBRESOURCE myresource;
	VertexClass* verticesPtr;
	D3DXVECTOR4* dptr;
	UINT stride = sizeof(VertexClass);
	UINT offset = 0;

	hr = context->Map(m_vertices, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr))
		return hr;
	verticesPtr = (VertexClass*)mappedResource.pData;
	memcpy(verticesPtr, (void*)pts, (sizeof(VertexClass)* 2));
	context->Unmap(m_vertices, 0);

	hr = context->Map(m_outlineColor, 0, D3D11_MAP_WRITE_DISCARD, 0, &myresource);
	if (FAILED(hr))
	{
		return hr;
	}
	dptr = (D3DXVECTOR4*)myresource.pData;
	*dptr = m_color;
	context->Unmap(m_outlineColor, 0);
	context->PSSetConstantBuffers(0, 1, &m_outlineColor);

	context->IASetVertexBuffers(0, 1, &m_vertices, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	context->Draw(2, 0);
	return hr;
}

void RayRenderClass::SetColor(float r, float g, float b, float a)
{
	m_color.x = r;
	m_color.y = g;
	m_color.z = b;
	m_color.w = a;
}