Texture2D surfaceTexture : register(t0);
Texture2D spriteTexture : register(t1);
SamplerState linearSampler : register(s0);


cbuffer PostFXData : register(b0)
{
    float4 colour;
}

struct VSInput
{
    float3 position : POSITION;
    float2 texcoord : TEXCOORD;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float4 colour : COLOUR;
    uint texId : TEXID;
};


PSInput VSMain(uint id : SV_VertexID)
{
    PSInput output;
	// From https://www.nickiebba.com/single-post/2017/08/23/post-processing-the-triangle-trick
	// Calculate the UV via the id
    output.texcoord = float2((id << 1) & 2, id & 2);

    output.position = float4(output.texcoord, 0, 1);
    output.position.x = output.position.x * 2 - 1;
    output.position.y = output.position.y * -2 + 1;

    return output;
}

float4 PSMain(PSInput input) : SV_TARGET
{
    float4 fluidColour = spriteTexture.Sample(linearSampler, input.texcoord);
    
    float4 bgColour = surfaceTexture.Sample(linearSampler, input.texcoord);
    
    for (int r = 0; r < 6; r++)
    {
        fluidColour.rgb *= fluidColour.a;
        fluidColour.a *= fluidColour.a;
    }
    
    float2 vOffset;
    vOffset.x = fluidColour.r - 0.5f;
    vOffset.y = fluidColour.g - 0.5f;
    
    float4 bgColourOff = surfaceTexture.Sample(linearSampler, input.texcoord + (vOffset * 0.01f));
    
    
    float highlight = vOffset.x + vOffset.y;
    float threshold = highlight * highlight;
    
    bgColourOff += float4(threshold, threshold, threshold, 0.f);
    bgColourOff *= float4(colour.rgb, 0.f);
    
    float3 finalColour = float3(((1.f - fluidColour.a) * bgColour.rgb * 0.9f) + (fluidColour.a * bgColourOff.rgb));

    return float4(finalColour.rgb, 1.f);
}