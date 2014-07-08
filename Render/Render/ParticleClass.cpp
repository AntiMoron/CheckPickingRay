#include "ParticleClass.h"


ParticleClass::ParticleClass()
{
}


ParticleClass::~ParticleClass()
{
}


HRESULT ParticleClass::Initialize(ID3D11Device* device,ID3D11DeviceContext* context)
{
	ReGenAvInitState();
	return S_OK;
}

HRESULT ParticleClass::Shutdown()
{
	return S_OK;
}

D3DXVECTOR3 ParticleClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 ParticleClass::GetRotation()
{
	return m_rotation;
}

D3DXVECTOR3 ParticleClass::GetScaling()
{
	return m_scaling;
}

void ParticleClass::Render()
{
	m_speed.y += GRAVITY;
	m_position += m_speed;
	if (m_position.y < -50.0)
	{
		ReGenInitState();
	}
}

void ParticleClass::ReGenAvInitState()
{
	m_speed = D3DXVECTOR3(RNG.GetFloat(-0.0003, 0.0003), RNG.GetFloat(-0.05, -0.01), RNG.GetFloat(-0.003, 0.003));
	m_position = D3DXVECTOR3(RNG.GetFloat(-1.0f * CHUNK_HEIGHT, CHUNK_HEIGHT), RNG.GetFloat(0.0f, -50.0f),
		RNG.GetFloat(-1.0f * CHUNK_WIDTH, CHUNK_WIDTH));
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scaling = D3DXVECTOR3(RNG.GetFloat(0.03, 0.06), RNG.GetFloat(0.03, 0.06), RNG.GetFloat(0.03, 0.06));
}

void ParticleClass::ReGenInitState()
{
	m_speed = D3DXVECTOR3(RNG.GetFloat(-0.0003, 0.0003), RNG.GetFloat(-0.05, -0.01), RNG.GetFloat(-0.003, 0.003));
	m_position = D3DXVECTOR3(RNG.GetFloat(-1.0f * CHUNK_HEIGHT,CHUNK_HEIGHT), 0.0f, 
		RNG.GetFloat(-1.0f * CHUNK_WIDTH,CHUNK_WIDTH));
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scaling = D3DXVECTOR3(RNG.GetFloat(0.03, 0.06), RNG.GetFloat(0.03, 0.06), RNG.GetFloat(0.03, 0.06));
}