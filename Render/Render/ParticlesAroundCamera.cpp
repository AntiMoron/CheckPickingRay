#include "ParticlesAroundCamera.h"


ParticlesAroundCamera::ParticlesAroundCamera()
{
}


ParticlesAroundCamera::~ParticlesAroundCamera()
{
}


HRESULT ParticlesAroundCamera::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	for (auto& _param : pts)
	{
		_param.Initialize(device,context);
	}
	return S_OK;
}


HRESULT ParticlesAroundCamera::Shutdown()
{
	for (auto& _param : pts)
	{
		_param.Shutdown();
	}
	return S_OK;
}

void ParticlesAroundCamera::Render(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera)
{
	pts[0].SetPosition(m_position);
	pts[1].SetPosition(m_position + D3DXVECTOR3(0.0f, 0.0f, CHUNK_HEIGHT));
	pts[2].SetPosition(m_position + D3DXVECTOR3(0.0f, 0.0f, -CHUNK_WIDTH));
	pts[3].SetPosition(m_position + D3DXVECTOR3(-CHUNK_WIDTH,0.0f,0.0f));
	pts[4].SetPosition(m_position + D3DXVECTOR3(-CHUNK_WIDTH, 0.0f, 0.0f));
	for (auto& _param : pts)
	{
		_param.Render(device,context);
	}
}