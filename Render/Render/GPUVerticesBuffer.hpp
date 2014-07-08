#pragma once

#include<D3D11.h>
#include<D3DX11.h>

template<typename source_type>
class GPUVerticesBuffer
{
public:
	GPUVerticesBuffer()
	{
	}
	~GPUVerticesBuffer()
	{
		;
	}

	//If the indices ptr is nullptr,then no index buffer would be initialized
	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context, source_type* verticesData, int verticesCount, WORD* indices = nullptr, UINT indicesCount = -1)
	{
		HRESULT hr = S_OK;
		m_inited = false;
		m_hasIndex = false;

		for (int i = 0;i<verticesCount; i++)
		{
			printf("%f %f %f\r\n", verticesData[i].pos[0], verticesData[i].pos[1], verticesData[i].pos[2]);
		}

		m_verticesCount = verticesCount;
		m_indicesCount = indicesCount;

		m_index = nullptr;
		m_vertices = nullptr;
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(source_type)* verticesCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = verticesData;
		hr = device->CreateBuffer(&bd, &InitData, &m_vertices);
		if (FAILED(hr))
		{
			printf("Vertex Buffer Create Failed\r\n");
			return hr;
		}
		// Set vertex buffer
		UINT stride = sizeof(source_type);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, &m_vertices, &stride, &offset);

		if (nullptr != indices)
		{
			for (int i = 0; i < indicesCount; i++)
			{
				printf("%u ",indices[i]); 
			}
			printf("\r\n");

			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(WORD)* indicesCount;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			ZeroMemory(&InitData,sizeof(InitData));
			InitData.pSysMem = indices;
			hr = device->CreateBuffer(&bd, &InitData, &m_index);
			if (FAILED(hr))
			{
				printf("Index buffer Create Failed\r\n");
				return hr;
			}
			context->IASetIndexBuffer(m_index, DXGI_FORMAT_R16_UINT, 0);
			m_hasIndex = true;
		}

		m_inited = true;
		return S_OK;
	}

	HRESULT Shutdown()
	{
		if (m_vertices)
		{
			m_vertices->Release();
			m_vertices = nullptr;
		}
		if (m_index)
		{
			m_index->Release();
			m_index = nullptr;
		}
		return S_OK;
	}

	HRESULT UpdateData(ID3D11Device* device, ID3D11DeviceContext* context, source_type* verticesData,int verticesCount)
	{
		HRESULT hr;
		return S_OK;
	}

	HRESULT Bind(ID3D11Device* device,ID3D11DeviceContext* context)
	{
		UINT stride = sizeof(source_type);
		UINT offset = 0;
		if (m_hasIndex == true)
		{
			context->IASetIndexBuffer(m_index, DXGI_FORMAT_R16_UINT, 0);
		}
		context->IASetVertexBuffers(0, 1, &m_vertices, &stride, &offset);
		return S_OK;
	}

	void Render(ID3D11Device* device,ID3D11DeviceContext* context)
	{
		Bind(device,context);
		if (m_hasIndex == true)
		{
			context->DrawIndexed(m_indicesCount,0,0);
		}
		else
		{
			context->Draw(m_verticesCount,0);
		}
	}

	bool isInited()const
	{
		return m_inited;
	}
private:

	bool m_inited;
	bool m_hasIndex;
	unsigned int m_verticesCount;
	unsigned int m_indicesCount;
	ID3D11Buffer* m_vertices;
	ID3D11Buffer* m_index;
};

