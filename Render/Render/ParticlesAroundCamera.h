#pragma once
#include"CameraClass.h"
#include"Particles.h"
class ParticlesAroundCamera
{
public:
	ParticlesAroundCamera();
	~ParticlesAroundCamera();

	HRESULT Initialize(ID3D11Device* device,ID3D11DeviceContext* context);
	HRESULT Shutdown();

	void Render(ID3D11Device* device, ID3D11DeviceContext* context,CameraClass* camera);
private:
	D3DXVECTOR3 m_position;
	Particles pts[5];//pos,forward ,backward,left,right
};

