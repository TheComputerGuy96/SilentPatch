struct VS_INPUT
{
	float4 Position   : POSITION;
	float2 Texture    : TEXCOORD0;
	float4 NightColor : COLOR0;
	float4 DayColor   : COLOR1;
};

struct VS_OUTPUT
{
	float4 Position   : POSITION;
	float2 Texture    : TEXCOORD0;
	float4 Color	  : COLOR0;
};

float4x4	viewProjMatrix : register(c0);
float2		fEnvVars : register(c4);
float4		AmbientLight : register(c5);
float4x4	world : register(c6);
float4x4	view : register(c10);
float4x4	proj : register(c14);

VS_OUTPUT NVC_vertex_shader( in VS_INPUT In )
{
	VS_OUTPUT Out;

//	Out.Position = mul(In.Position, viewProjMatrix);
	Out.Position = mul(proj, mul(view, mul(world, In.Position)));
	Out.Texture = In.Texture;

	Out.Color.rgb = (In.DayColor.rgb * (1.0-fEnvVars[0]) + In.NightColor.rgb * fEnvVars[0]) + AmbientLight.rgb;
	Out.Color.a = In.DayColor.a * (255.0/128.0) * fEnvVars[1];
	//Out.Color.rgb = In.DayColor.rgb + AmbientLight.rgb;
	Out.Color = saturate(Out.Color);

	return Out;
}