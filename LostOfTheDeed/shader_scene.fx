//=============================================================================
// transform.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Basic FX that simply transforms geometry from local space to
// homogeneous clip space, and draws the geometry in wireframe mode.
//=============================================================================

//uniform extern float4x4 gWVP;
uniform extern float4x4 gUIWorld;
uniform	extern float4x4 gUIView;
uniform extern float4x4 gUIProj;
uniform	extern float4x4	gUIMove;
uniform extern texture gTex;
uniform extern bool		alphaEnable;
//uniform extern float	alpha;
// Define a vertex shader output structure; that is, a structure
// that defines the data we output from the vertex shader.  Here,
// we only output a 4D vector in homogeneous clip space.  The
// semantic ": POSITION0" tells Direct3D that the data returned
// in this data member is a vertex position.
struct OutputVS
{
    float4 posH : POSITION0;
	float2 texCord : TEXCOORD0;
	float4 color : COLOR0;
 //   float4 spec    : COLOR1;
};

sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = Anisotropic;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 8;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

// Define the vertex shader program.  The parameter posL
// corresponds to a data member in the vertex structure.
// Specifically, it corresponds to the data member in the
// vertex structure with usage D3DDECLUSAGE_POSITION and
// index 0 (as specified by the vertex declaration).
OutputVS TransformVS(float3 posL : POSITION0,
					float2 texC : TEXCOORD0,
					float3 normal : NORMAL0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;

	float4x4 gWVP = mul( gUIWorld, gUIMove );

	gWVP = mul( gWVP, gUIView );
	gWVP = mul( gWVP, gUIProj );

	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	//outVS.posH = mul( outVS.posH, gUITransform);

	float3 aaa = { 3, 0, -0.5 };

	float b = dot( aaa, normal );

	b = b/(length(aaa));
	outVS.texCord = texC;

	outVS.color.x = 1.0f;
	outVS.color.y = 1.0f;
	outVS.color.z = 1.0f;
	outVS.color.w = 0.0f;

	if ( b > 0 )
	{
		outVS.color.x += b;
		outVS.color.y += b;
		outVS.color.z += b;
	}
	// Done--return the output.
    return outVS;
}

// Define the pixel shader program.  Just return a 4D color
// vector (i.e., first component red, second component green,
// third component blue, fourth component alpha).  Here we
// specify black to color the lines black.

float4 TransformPS(float4 c : COLOR0, float2 tex0 : TEXCOORD0) : COLOR
{
/*	float4 texColor = tex2D(TexS, tex0);
	//float3 diffuse = c.rgb * texColor.rgb;
	float3 texColor1 = tex2D(TexS, tex0).rgb;
    //return float4(texColor1 + c.rgb, texColor.a*c.a);
	return float4( 255.0,0.0,0.0,0.0);
*/
	float4 texColor = tex2D(TexS, tex0);
//	float alphaa = texColor.a;
/*	texColor.r*=alphaa;
	texColor.g*= alphaa;
	texColor.b*= alphaa;*/
//	texColor.a *= alpha;
	return texColor;
}

technique TransformTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 TransformVS();
        pixelShader  = compile ps_2_0 TransformPS();

		// Specify the render/device states associated with this pass.
		//FillMode = Wireframe;

		AlphaBlendEnable = alphaEnable;
		//AlphaBlendEnable = false;

    }
}
