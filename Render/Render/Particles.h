#pragma once
#include"BlockClass.h"
#include"ParticleClass.h"

class Particles
{
public:
	Particles();
	~Particles();

	HRESULT Initialize(ID3D11Device* device,ID3D11DeviceContext* context);
	HRESULT Shutdown();

	void SetPosition(D3DXVECTOR3 position);
	void Render(ID3D11Device* device, ID3D11DeviceContext* context);
private:
	D3DXVECTOR3 m_position;
	ParticleClass m_data[1000];
	BlockClass m_block;
};