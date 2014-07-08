#pragma once
#include<memory.h>

struct VertexClass
{
	VertexClass()
	{
		memset(pos,0,sizeof(pos));
		memset(nor,0,sizeof(nor));
		memset(col,0,sizeof(col));
		memset(tex,0,sizeof(tex));
	}

	VertexClass(float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8,
		float _9,float _10,float _11,float _12,float _13,float _14)
	{
		pos[0] = _1;
		pos[1] = _2;
		pos[2] = _3;
		pos[3] = _4;
		nor[0] = _5;
		nor[1] = _6;
		nor[2] = _7;
		nor[3] = _8;
		col[0] = _9;
		col[1] = _10;
		col[2] = _11;
		col[3] = _12;
		tex[0] = _13;
		tex[1] = _14;
	}

	float pos[4];
	float nor[4];
	float col[4];
	float tex[2];
};