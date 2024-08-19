Texture2D tex : register(t0);
SamplerState sam : register(s0);

float4 main(float4 position : SV_POSITION, float2 texCoord : TEXCOORD0) : SV_TARGET
{
    return tex.Sample(sam,texCoord);
}