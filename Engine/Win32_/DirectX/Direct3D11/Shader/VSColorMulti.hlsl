cbuffer CBuf
{
    matrix transform;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    uint tid : TEXCOORD0;
};

VSOutput main(float3 pos : POSITION, uint tid : SV_InstanceID)
{
    VSOutput output;

    output.position = mul(float4(pos, 1.0f), transform);
    output.tid = tid;

    return output;
}