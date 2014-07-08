#include "CameraClass.h"

CameraClass::CameraClass()
{
	;
}

CameraClass::~CameraClass()
{
	;
}

HRESULT CameraClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{

	m_buffer.Initialize(device, context, 1);
	D3DXMatrixIdentity(&mat.world);
	D3DXMatrixIdentity(&mat.projection);
	D3DXMatrixIdentity(&mat.view);

	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_step = 0.5;
	m_fov = 40.0f;

	D3DXMatrixPerspectiveFovLH(&mat.projection, m_fov * 0.017453292f, SCREENWIDTH / (float)SCREENHEIGHT, 0.000001f, 100000.0f);

	D3DXVECTOR3 Eye = m_position;
	D3DXVECTOR3 At(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Up(0.0f, 0.0f, 1.0f);
	D3DXMatrixLookAtLH(&mat.view, &Eye, &At, &Up);
	m_headingDir = At;
	m_upDirection = Up;

	GPUData data;
	D3DXMatrixTranspose(&data.view, &mat.view);
	D3DXMatrixTranspose(&data.projection, &mat.projection);
	D3DXMatrixTranspose(&data.world, &mat.world);

	m_buffer.UpdateData(&data);
	m_buffer.UpdateGpu(device, context);
	m_buffer.BindVertexShader(device, context);
	return S_OK;
}

HRESULT CameraClass::Shutdown()
{
	m_buffer.Shutdown();
	return S_OK;
}

void CameraClass::SetPosition(D3DXVECTOR3 val)
{
	m_position = val;
}

void CameraClass::SetRotation(D3DXVECTOR3 val)
{
	m_rotation = val;
}

void CameraClass::SetStep(float val)
{
	m_step = val;
}


void CameraClass::MoveForward()
{
	m_moveSpeed = m_headingDir;
}

void CameraClass::MoveBackward()
{
	m_moveSpeed = -m_headingDir;
}


void CameraClass::UpdateCamera(ID3D11Device* device, ID3D11DeviceContext* context)
{

	D3DXVec3Normalize(&m_moveSpeed, &m_moveSpeed);
	m_position += m_step * m_moveSpeed;

	D3DXMatrixIdentity(&mat.world);
	D3DXMatrixIdentity(&mat.projection);
	D3DXMatrixIdentity(&mat.view);

	D3DXMatrixPerspectiveFovLH(&mat.projection, m_fov * 0.017453292f, SCREENWIDTH / (float)SCREENHEIGHT, 0.000001f, 100000.0f);

	D3DXVECTOR3 Eye = m_position;
	D3DXVECTOR3 At(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

	float pitch = m_rotation.x * 0.0174532925f;
	float yaw = m_rotation.y * 0.0174532925f;
	float roll = m_rotation.z * 0.0174532925f;
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	m_lefthandSide = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&At, &At, &rotationMatrix);
	D3DXVec3TransformCoord(&m_upDirection, &Up, &rotationMatrix);
	D3DXVec3TransformCoord(&m_lefthandSide, &m_lefthandSide, &rotationMatrix);
	m_headingDir = At;
	At += Eye;

	D3DXMatrixLookAtLH(&mat.view, &Eye, &At, &Up);

	GPUData data;
	D3DXMatrixTranspose(&data.view, &mat.view);
	D3DXMatrixTranspose(&data.projection, &mat.projection);
	D3DXMatrixTranspose(&data.world, &mat.world);

//	printf("%f %f %f\r\n",m_rotation.x,m_rotation.y,m_rotation.z);

	m_buffer.UpdateData(&data);
	m_buffer.UpdateGpu(device, context);
	m_buffer.BindVertexShader(device, context);
	m_moveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CameraClass::SetFov(float val)
{
	m_fov = 0.017453292f * val;
	D3DXMatrixPerspectiveFovLH(&mat.projection, m_fov, SCREENWIDTH / (float)SCREENHEIGHT, 0.0000001f, 100000.0f);
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return m_rotation;
}

D3DXMATRIX CameraClass::GetProjectionMatrix()
{
	return mat.projection;
}
D3DXMATRIX CameraClass::GetViewMatrix()
{
	return mat.view;
}
D3DXMATRIX CameraClass::GetWorldMatrix()
{
	return mat.world;
}
