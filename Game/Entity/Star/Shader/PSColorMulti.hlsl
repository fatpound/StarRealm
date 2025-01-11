StructuredBuffer<float4> vertex_colors : register(t0);

struct PSInput
{
    float4 position : SV_POSITION;
    uint tid : TEXCOORD0;
};

float4 main(PSInput input) : SV_Target
{
    return vertex_colors[input.tid % vertex_colors.Length];
}