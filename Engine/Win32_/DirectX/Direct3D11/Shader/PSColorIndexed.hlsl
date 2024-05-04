cbuffer CBuf
{
    float4 vertex_colors[6];
};

float4 main(uint tid : SV_PrimitiveID) : SV_Target
{
    return vertex_colors[tid % 6];
}