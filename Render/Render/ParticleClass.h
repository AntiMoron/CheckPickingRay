#pragma once
#include<D3D11.h>
#include<D3DX11.h>
#include<D3DX10math.h>
#include"BlockClass.h"
#include"RandomGenerator.h"
#define CHUNK_HEIGHT 100.0f
#define CHUNK_WIDTH CHUNK_HEIGHT
#define GRAVITY -0.01
class ParticleClass
{
public:
	ParticleClass();
	~ParticleClass();
	
	HRESULT Initialize(ID3D11Device* device,ID3D11DeviceContext* context);
	HRESULT Shutdown();
	void Render();

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetScaling();
	void ReGenAvInitState();//���ȷֲ��ط��ó�ʼֵ
private:
	void ReGenInitState();//�ڿ��˷��ó�ʼֵ

	D3DXVECTOR3 m_speed;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scaling;
};

