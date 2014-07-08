#pragma once
#include<stdio.h>
#include<D3D11.h>
#include<D3DX11.h>
#include<D3DX10math.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<regex>
#include <iostream>
#include"SystemVar.h"
#include"VertexClass.h"
#include"MaterialSet.h"
#include"CameraClass.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma comment(lib,"assimp.lib")

using namespace std;

class ModelClass
{
public:
	ModelClass();
	ModelClass(const ModelClass& other);
	~ModelClass();
	ModelClass& operator = (const ModelClass& other);

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context, const char* filename);
	HRESULT Render(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT Shutdown();

	D3DXVECTOR3 GetMaxBV();
	D3DXVECTOR3 GetMinBV();

	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetScaling();
	D3DXVECTOR3 GetPosition();

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetScaling(D3DXVECTOR3 sca);

	void SetPosition(float, float, float, ID3D11Device*, ID3D11DeviceContext*);
	void SetRotation(float, float, float, ID3D11Device*, ID3D11DeviceContext*);
	void SetScaling(float, float, float, ID3D11Device*, ID3D11DeviceContext *);

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetScaling(float, float, float);

	void SetTransparency(ID3D11Device *device, ID3D11DeviceContext * context, float trans);



	inline bool isInited()
	{
		return inited;
	}

private:

	bool AssimpRead(ID3D11Device* device, ID3D11DeviceContext* context, const string& filename);
	bool inited;

	vector<int> m_mIndices;//实际有贴图SRV的索引
	vector<int> m_matIndices;//实际所有的索引
	MaterialSet m_mtlSet;
	vector<vector<VertexClass> >vec;

	struct FLOAT3{ float var[3]; };

	D3DXVECTOR3 m_maxBV;		//AABB包围盒 最大点坐标
	D3DXVECTOR3 m_minBV;		//AABB包围盒 最小点坐标

	std::string* filetext;

	D3DXVECTOR3  m_position, m_scaling, m_rotation;
	struct Propertys
	{
		D3DXMATRIX	 TranslationMatrix;
		D3DXMATRIX   ScalingMatrix;
		D3DXMATRIX	 RotationMatrix;
	}propertys;
	struct Factors
	{
		float transparent;
		float rev1;
		float rev2;
		float rev3;
	}factors;

	std::vector<D3DXVECTOR4> m_colors;
	ID3D11Buffer** m_ModelBuffer;
	ID3D11Buffer* m_ModelProperty;
	ID3D11Buffer* m_RenderFactors;
	ID3D11Buffer* m_vertexColor;
};

