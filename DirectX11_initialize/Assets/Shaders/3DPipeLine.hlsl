//3D空間に表示させるポリゴン用のシェーダ(テクスチャなし)

struct VS_IN
{
    float4 pos : POSITION0;
    float4 col : COLOR0;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};

cbuffer ConstantBuffer
{
    float4x4 World;         //ワールド変換行列
    float4x4 View;          //ビュー変換行列
    float4x4 Projection;    //透視射影変換行列
}

VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;

    output.pos = mul(input.pos, World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);
    output.col = input.col;
    return output;
}

float4 ps_main(PS_IN input) : SV_Target
{
    return input.col;
}