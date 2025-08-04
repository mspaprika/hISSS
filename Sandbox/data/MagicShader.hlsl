// We want to use some of Play3ds built-in standard macros.
PLAY3D_PER_FRAME_CONSTANTS
//PLAY3D_PER_DRAW_CONSTANTS
//PLAY3D_LIGHT_CONSTANTS
//PLAY3D_MESH_VS_INPUTS


//cbuffer MaterialConstantData : register(PLAY3D_REG_MATERIAL_CONSTANTS)
//{
//    float4 diffuseColor;
//    float4 specularColor;
   
//};

cbuffer myConstanttData : register(PLAY3D_REG_MATERIAL_CONSTANTS)
{
    float a;
    float b;
    float c;
    float d;
   
   
};
// Vertex Shader Input
// In this example we generate the vertices in the vertex shader.
struct VSInput
{
    uint vertexId : SV_VertexID;
};

// Pixel Shader Input
// This can be completely customized as long as it matches the output of your Vertex Shader.
struct PSInput
{
    float4 position : SV_POSITION; //<< This attribute must exist.
    float2 uv : TEXCOORD;
};

// The Vertex Shaders entry point function
// This is called on every vertex in the mesh.
PSInput VS_Main(VSInput input)
{
	// Interesting article on this technique:
	// https://wallisc.github.io/rendering/2021/04/18/Fullscreen-Pass.html 

    PSInput output;
    output.uv = float2((input.vertexId << 1) & 2, input.vertexId & 2);
    output.position = float4(output.uv * float2(2, -2) + float2(-1, 1), 0, 1);
    return output;
}

// Passing the offscreen through BindGlobalTexture
Texture2D g_offscreenTexture : register(PLAY3D_REG_GLOBAL_SRV0);
SamplerState g_offscreenSampler : register(PLAY3D_REG_LINEAR_WRAP_SAMPLER);


// The Pixel Shaders entry point function
// This is called on every generated pixel (fragment).
float4 PS_Main(PSInput input) : SV_TARGET
{

    float3 F1 = g_offscreenTexture.Sample(g_offscreenSampler, input.uv + float2(0.01, 0)).rgb;
    float3 F2 = g_offscreenTexture.Sample(g_offscreenSampler, input.uv).rgb;

    return float4(F1 * 0.5 + F2 * 0.5, 1.0);
}