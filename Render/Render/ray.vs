
cbuffer matrices : register( b1 )
{
    matrix View;
    matrix Projection;
    matrix World;
};

cbuffer PRS : register(b2)
{
	matrix translation;
	matrix scaling;
	matrix rotation;
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
	float4 Nor : NORMAL;
	float4 Color : COLOR;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VSEntry( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
	output.Pos = input.Pos;
    output.Pos = mul( output.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    return output;
}
