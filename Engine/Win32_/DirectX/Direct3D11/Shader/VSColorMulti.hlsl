cbuffer CBuf
{
    matrix transform;
};

struct VSInput
{
    float3 position : POSITION;
    uint tid : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    uint tid : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = mul(float4(input.position, 1.0f), transform);
    output.tid = input.tid;

    return output;
}