//2Dテクスチャを表示する

struct VS_INPUT
{
	float3 Position : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float4 Color : TEXCOORD0;
	float2 UV : TEXCOORD1;
};

void vsMain(
	in VS_INPUT In,
	out VS_OUTPUT Out
)
{
	Out.Position.xyz = In.Position.xyz;
	Out.Position.w = 1.0f;
	Out.Color = In.Color;
	Out.UV = In.UV;
}

typedef VS_OUTPUT PS_INPUT;


Texture2D diffuse : register(t0);
SamplerState samplerDiffuse : register(s0);

void psMain(
	in PS_INPUT In,
	out float4 OutColor : SV_Target0
)
{
	float4 tex = diffuse.Sample(samplerDiffuse, In.UV);
	OutColor = In.Color * tex;
}
