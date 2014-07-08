#include "PickingClass.h"


PickingClass::PickingClass()
{
}


PickingClass::~PickingClass()
{
}

HRESULT PickingClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_origin = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_direction = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return S_OK;
}

HRESULT PickingClass::Shutdown()
{
	return S_OK;
}

void PickingClass::UpdateRay(int mousex,int mousey,CameraClass* camera)
{
	float pointX = ((2.0f * (float)mousex) / (float)SCREENWIDTH) - 1.0f;
	float pointY = (((2.0f * (float)mousey) / (float)SCREENHEIGHT) - 1.0f) * -1.0f;
	D3DXMATRIX projectionMatrix = camera->GetProjectionMatrix();
	D3DXMATRIX viewMatrix = camera->GetViewMatrix();
	D3DXMATRIX worldMatrix = camera->GetWorldMatrix();
	D3DXMATRIX inverseViewMatrix;
	D3DXMATRIX inverseProjection;
	D3DXMatrixInverse(&inverseProjection,NULL,&projectionMatrix);
	D3DXMatrixInverse(&inverseViewMatrix, NULL, &viewMatrix);
	D3DXVECTOR4 mouse_clip(pointX,pointY,-0.001f,1.0f);
	D3DXMATRIX mulMatrix = inverseViewMatrix * inverseProjection;
	m_origin = camera->GetPosition();
	D3DXVec3TransformCoord(&m_direction, &m_direction, &mulMatrix);
	m_direction -= m_origin;
	D3DXVec3Normalize(&m_direction, &m_direction);
}

bool PickingClass::IntersectBox()
{
	return false;
}