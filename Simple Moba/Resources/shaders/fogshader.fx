float4x4 World;
float4x4 View;
float4x4 Projection;

float3 LightPos;
float3 AmbientColor;
float3 DiffuseColor;

struct VertexOut
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
};

VertexOut VShader(float4 Pos : POSITION, float3 Normal : NORMAL)
{
	VertexOut Vert = (VertexOut)0;

	float3 FogColor = float3(.9, .9, 1);
	float3 FogDifference;
	float3 FinalColor;

	Pos = mul(Pos, World);
	Normal = mul(Normal, World);
	float3 LightVec = normalize(LightPos - Pos);

	DiffuseColor = dot(Normal, LightVec) * DiffuseColor;
	DiffuseColor = max(DiffuseColor, 0);

	FinalColor = DiffuseColor + AmbientColor;

	float4x4 Transform;
	Transform = mul(View, Projection);
	Vert.Pos = mul(Pos, Transform);

	FogDifference = FogColor - FinalColor;
	FogDifference = FogDifference * Vert.Pos.z / 100;
	FinalColor = FogDifference + FinalColor;
	FinalColor = min(FinalColor, FogColor);

	Vert.Color.rgb = FinalColor;

	return Vert;
}

technique FirstTechnique
{
	pass FirstPass
	{
		Lighting = TRUE;
		ZEnable = TRUE;

		VertexShader = compile vs_2_0 VShader();
	}
}