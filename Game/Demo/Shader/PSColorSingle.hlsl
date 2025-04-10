cbuffer CBuf
{
    float4 the_color;
};

float4 main() : SV_Target
{
    return the_color;
}