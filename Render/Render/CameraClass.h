#pragma once
#include<D3D11.h>
#include<D3DX11.h>
#include<D3DX10math.h>
#include"GPUConstantBuffer.hpp"

class CameraClass
{
public:
	CameraClass();
	~CameraClass();

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT Shutdown();

	void SetPosition(D3DXVECTOR3 val);
	void SetRotation(D3DXVECTOR3 val);
	void SetStep(float val);
	void SetFov(float val);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();


	D3DXMATRIX GetProjectionMatrix();
	D3DXMATRIX GetViewMatrix();
	D3DXMATRIX GetWorldMatrix();

	void MoveForward();
	void MoveBackward();


	void UpdateCamera(ID3D11Device* device, ID3D11DeviceContext* context);

private:
	struct GPUData
	{
		D3DXMATRIX view;
		D3DXMATRIX projection;
		D3DXMATRIX world;
	}mat;

	float m_fov;
	float m_step;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_moveSpeed;
	D3DXVECTOR3 m_headingDir;
	D3DXVECTOR3 m_upDirection;
	D3DXVECTOR3 m_lefthandSide;		//相对摄像机前进方向的左手方向
	GPUConstantBuffer<GPUData> m_buffer;
};