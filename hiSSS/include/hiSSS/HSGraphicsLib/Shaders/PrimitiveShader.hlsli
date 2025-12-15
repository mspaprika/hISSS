cbuffer DrawConstants : register(b0)
{
    float4x4 mvp;
    float depth;
}

struct VSInput
{
    float3 position : POSITION;
    float3 color    : COLOUR;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float3 color    : COLOUR; 
};

// Vertex Shader
PSInput VSMain(VSInput input)
{
    PSInput output;

    output.position = mul(mvp, float4(input.position, 1.0f)); // Set z/depth and w to 1.0f
    output.color = input.color;

    return output;
}

// Pixel Shader
float4 PSMain(PSInput input) : SV_TARGET
{
    // Directly use the color from the vertex shader
    return float4(input.color, 1.0f); // Use the color from input, set alpha to 1.0
}
