// We want to use some of Play3ds built-in standard macros.
PLAY3D_PER_FRAME_CONSTANTS
PLAY3D_PER_DRAW_CONSTANTS
PLAY3D_LIGHT_CONSTANTS
PLAY3D_MESH_VS_INPUTS

// Pixel Shader Input
// This can be completely customized as long as it matches the output of your Vertex Shader.
struct PSInput
{
	float4 position : SV_POSITION; //<< This attribute must exist.
};

// The Vertex Shaders entry point function
// This is called on every vertex in the mesh.
PSInput VS_Main(VSInput input)
{
	PSInput output;
	output.position = mul(mvpMtx, float4(input.position.xyz, 1.0f));
	return output;
}

// The Pixel Shaders entry point function
// This is called on every generated pixel (fragment).
float4 PS_Main(PSInput input) : SV_TARGET
{
	return float4(1,1,1,1);
}