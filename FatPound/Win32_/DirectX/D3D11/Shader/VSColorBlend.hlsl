cbuffer CBuf
{
    matrix transform;
};

struct VSOut
{
    float3 color : COLOR;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITION, float3 col : COLOR)
{
    VSOut output;

    output.pos = mul(float4(pos, 1.0f), transform);
    output.color = col;

    return output;
}