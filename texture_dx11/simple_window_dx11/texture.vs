cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 tex		: TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 tex		: TEXCOORD;
};

PixelInputType TextureVertexShader(VertexInputType input)
{
	input.position.w = 1.0f;
	PixelInputType output;
	output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
	//output.position = input.position;
	output.color = input.color;
	output.tex = input.tex;
	return output;
}