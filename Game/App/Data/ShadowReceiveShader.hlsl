// We want to use some of Play3ds built-in standard macros.
PLAY3D_PER_FRAME_CONSTANTS
PLAY3D_PER_DRAW_CONSTANTS
PLAY3D_LIGHT_CONSTANTS
PLAY3D_MESH_VS_INPUTS

// Custom Shadow Constant Buffer
cbuffer ShadowConstantData : register(PLAY3D_REG_GLOBAL_CBV0)
{
	float4x4 lightMatrix;
};

// Pixel Shader Input
// This can be completely customized as long as it matches the output of your Vertex Shader.
struct PSInput
{
	float4 position : SV_POSITION; //<< This attribute must exist.
	float4 colour : COLOUR;
	float3 normal : NORMAL;
	float2 uv : UV;

	float4 pos_WS : POS_WS; // << position in world space.
	float4 pos_LS : POS_LS; // << position in light space.
};

// The Vertex Shaders entry point function
// This is called on every vertex in the mesh.
PSInput VS_Main(VSInput input)
{
	PSInput output;

	output.pos_WS = mul(worldMtx, float4(input.position.xyz, 1.0f));
	output.pos_LS = mul(lightMatrix, float4(output.pos_WS.xyz, 1.0));

	output.position = mul(mvpMtx, float4(input.position.xyz, 1.0f));
	output.colour = pow(input.colour, 2.2); // Gamma correct from sRGB.
	output.normal = mul(normalMtx, float4(input.normal.xyz, 0.0f));
	output.uv = input.uv;

	return output;
}

// Passing the diffuse material texture
Texture2D g_diffuseTexture : register(PLAY3D_REG_MATERIAL_TEXTURE0);
SamplerState g_diffuseSampler : register(PLAY3D_REG_MATERIAL_SAMPLER0);

// Passing the shadow map through BindGlobalTexture
Texture2D g_shadowMapTexture : register(PLAY3D_REG_GLOBAL_SRV0);
SamplerState g_shadowMapSampler : register(PLAY3D_REG_GLOBAL_SAMPLER0);


// Constants containing pixel offsets for PCF filter.
static float2 g_pcfOffset[9] =
{
	float2(-1, 1), float2(0, 1), float2(1, 1),
	float2(-1, 0), float2(0, 0), float2(1, 0),
	float2(-1, -1), float2(0, -1), float2(1, -1)
};


// The Pixel Shaders entry point function
// This is called on every generated pixel (fragment).
float4 PS_Main(PSInput input) : SV_TARGET
{
	// Sample the Diffuse Colour
	float3 Cd = pow(g_diffuseTexture.Sample(g_diffuseSampler, input.uv).rgb * input.colour, 2.2);
	float3 Cs = saturate(Cd * 8.0);
	float3 Cl = float4(pow(lightColour[0], 1));


	// Perspective correct world position
	float3 pos_WS = input.pos_WS.xyz / input.pos_WS.w;

	// Properties typical for lighting equations
	// Working in world space in this example.
	float3 N = normalize(input.normal);
	float3 L = normalize(lightDir[0]);
	float3 V = normalize(viewPosition.xyz - pos_WS);
	
	float d = length(V);
	V /= d;

	float3 H = normalize(L + V);

	float dotNL = dot(N, L);
	float dotNH = dot(N, H);

	// Perspective correct the lightspace position.
	float3 pos_LS = input.pos_LS.xyz / input.pos_LS.w;

	// Obtain shadown map UV coords from lightspace coordinates.
	float2 lightUV = pos_LS.xy * 0.5 + 0.5; 

	// Y Flip for DirectX textures.
	lightUV.y = 1.0 - lightUV.y;

	// Obtain depth from lightspace coordinates.
	// Apply a bias to avoid shadow achne artifacts.
	float bias = max(0.001 * (1.0 - dotNL), 0.0001);
	float depth = pos_LS.z - bias;

	// Shadow Sampling
	float shadowPCF = 0.0;
	const float pixelScale = 1.0 / 2048;
	for (int i = 0; i < 9; i++)
	{
		float sampledDepth = g_shadowMapTexture.Sample(g_shadowMapSampler, lightUV.xy + g_pcfOffset[i] * pixelScale);
		shadowPCF += depth > sampledDepth ? 1.0 : 0.0;
	}

	shadowPCF /= 9.0;

	// Calculate final lighting
	float Id = saturate(dotNL) * (1.0 - shadowPCF);
	float Is = pow(saturate(dotNH), 4.0 * 16.0) * (dotNL > 0.f) * (1.0 - shadowPCF);

	float4 brdf = float4(Cd * Cl * Id + Cs * Cl * Is, 1);

	return pow(brdf, 0.45454545);
}