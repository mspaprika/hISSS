// We want to use some of Play3ds built-in standard macros.
PLAY3D_PER_FRAME_CONSTANTS
PLAY3D_PER_DRAW_CONSTANTS
PLAY3D_LIGHT_CONSTANTS
PLAY3D_MESH_VS_INPUTS

// Material Constants are managed by materials.
// You can customise the data as you like here
// but it must match the Material's Constant Buffer
cbuffer MaterialConstantData : register(PLAY3D_REG_MATERIAL_CONSTANTS)
{
	float4 materialParams;
};

// Pixel Shader Input
// This can be completely customized as long as it matches the output of your Vertex Shader.
struct PSInput
{
	float4 position : SV_POSITION; //<< This attribute must exist.
	float4 colour : COLOUR;
	float3 normal : NORMAL;
	float2 uv : UV;
};

SamplerState g_linearSampler : register(PLAY3D_REG_LINEAR_WRAP_SAMPLER);
Texture2D g_noise : register(PLAY3D_REG_GLOBAL_SRV0);

// The Vertex Shaders entry point function
// This is called on every vertex in the mesh.
PSInput VS_Main(VSInput input)
{
	PSInput output;
	

    //input.position.y = (sin((input.position.y + time.x) * 1.5) % 50) + sin(input.uv.y + time.x) * 0.5;
    //input.position.x = (sin((input.uv.x + time.x) * 1.5) % 50);
   

	output.position = mul(mvpMtx, float4(input.position.xyz, 1.0f));
	output.colour = pow(input.colour, 2.2); // Gamma correct from sRGB.
	output.normal = mul(normalMtx, float4(input.normal.xyz, 0.0f));
	output.uv = input.uv;

	return output;
}

// The Pixel Shaders entry point function
// This is called on every generated pixel (fragment).
float4 PS_Main(PSInput input) : SV_TARGET
{
	//float noise =  g_noise.Sample(g_linearSampler, input.uv * 0.2).x;
	//return float4(input.uv * materialParams.x * noise, 0, 1);
    float3 N = normalize(input.normal);
    float3 L = normalize(lightDir[0]);
    float intensityDiffuse = saturate(dot(N, L));
    return float4((time.zw * intensityDiffuse * 0.001), 0, 1);
    //return float4((input.normal) * 1.5, 1);
}