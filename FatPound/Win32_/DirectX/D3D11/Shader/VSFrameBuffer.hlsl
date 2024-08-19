struct VSOut
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
};

VSOut main(float4 position : POSITION, float2 texCoord : TEXCOORD0)
{
    VSOut output;

    output.position = position;
    output.texCoord = texCoord;

    return output;
}