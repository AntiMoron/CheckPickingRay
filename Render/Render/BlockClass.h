#pragma once
#include <stdio.h>
#include "VertexClass.h"
#include"GPUConstantBuffer.hpp"
#include"GPUVerticesBuffer.hpp"
#include <d3dx10math.h>

class BlockClass
{
public:
	BlockClass(void);
	~BlockClass(void);
	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context);
	void Render(ID3D11Device* device, ID3D11DeviceContext* context);
	void SetPosition(D3DXVECTOR3 position);
	void SetRotation(D3DXVECTOR3 rotation);
	void SetScaling(D3DXVECTOR3 scaling);

	HRESULT Shutdown();
private:
	friend class SkyClass;
	friend class Rectangle2DClass;
	VertexClass pts[36];
	D3DXVECTOR3  m_position, m_scaling, m_rotation;
	struct Propertys
	{
		D3DXMATRIX	 TranslationMatrix;
		D3DXMATRIX   ScalingMatrix;
		D3DXMATRIX	 RotationMatrix;
	}propertys;
	GPUVerticesBuffer<VertexClass> m_vertBuffer;
	GPUConstantBuffer<Propertys> m_PRS;
};