//3D空間に表示させるポリゴン用のシェーダ(テクスチャなし)
/*頂点シェーダー&ピクセルシェーダー*/
Texture2D g_texture : register(t0);
SamplerState samLinear : register(s0);

struct VS_IN
{
    float4 pos : POSITION0;
    float4 col : COLOR0;
    float4 nor : NORMAL0;
    float2 Tex : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 Tex : TEXCOORD;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 Tex : TEXCOORD;
};

cbuffer ConstantBuffer
{
    float4x4 World;         //ワールド変換行列
    float4x4 View;          //ビュー変換行列
    float4x4 Projection;    //透視射影変換行列
    float4 Light;
}

VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;
    float3 nor;
    float  col;

    output.pos = mul(input.pos, World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);

    //テクスチャ
    output.Tex = input.Tex;

    nor = mul(input.nor, World).xyz;
    nor = normalize(nor);

    col = saturate(dot(nor, (float3)Light));
    col = col * 0.5f + 0.5f;

    output.col = input.col * float4(col, col, col, 1.0f);


    return output;
}

float4 ps_main(PS_IN input) : SV_Target
{
    /*float3 nor;
    float  col;
    VS_IN vs_input;
    nor = mul(vs_input.nor, World).xyz;
    nor = normalize(nor);

    col = saturate(dot(nor, (float3)Light));
    col = col * 0.5f + 0.5f;*/

    //return g_texture.Sample(samLinear, input.Tex) *0.3 + input.col *0.7; //+ input.col;
    //頂点シェーダで求めた色とテクスチャの色を加算
    return input.col + g_texture.Sample(samLinear, input.Tex) * 1.0;
    //return input.col;
}