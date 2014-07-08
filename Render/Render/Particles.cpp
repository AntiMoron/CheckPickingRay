#include "Particles.h"


Particles::Particles()
{
}


Particles::~Particles()
{
}

HRESULT Particles::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_block.Initialize(device,context);
	for (auto& _param : m_data)
	{
		_param.Initialize(device,context);
	}
	m_position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return S_OK;
}

HRESULT Particles::Shutdown()
{
	m_block.Shutdown();
	for (auto& _param : m_data)
	{
		_param.Shutdown();
	}
	return S_OK;
}


void Particles::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
}
void Particles::Render(ID3D11Device* device, ID3D11DeviceContext* context)
{
	for (auto& _param : m_data)
	{
		_param.Render();
		m_block.SetPosition(m_position + _param.GetPosition());
		m_block.SetRotation(_param.GetRotation());
		m_block.SetScaling(_param.GetScaling());
		m_block.Render(device,context);
	}
}