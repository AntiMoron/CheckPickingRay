#pragma once
#include"CameraClass.h"
//#include"xnaCollision.h"
#include"SystemVar.h"

class PickingClass
{
public:
	PickingClass();
	~PickingClass();
	HRESULT Initialize(ID3D11Device* device,ID3D11DeviceContext* context);
	HRESULT Shutdown();

	void UpdateRay(int x,int y,CameraClass* camera);
	bool IntersectBox();
//private:
	D3DXVECTOR3 m_origin,m_direction;
};

