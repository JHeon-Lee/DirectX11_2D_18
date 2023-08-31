struct VertexInput
{
	float4 position : POSITION0;
	float2 uv		: TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv		: TEXCOORD0;
};

cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
};

cbuffer ShadedBuffer : register(b0)
{
	int _selection;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _projection);
	
	output.uv = input.uv;
	return output;
}

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
	float4 resultColor = 0;
	
	if (_selection == 1)
	{
		return color;
	}
	else if (_selection == 2)
	{
		// AM
		float3 temp = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
		resultColor = float4(temp, color.a);
	}
	else if (_selection == 3)
	{
		// Sepia
		float3 sepia = float3(0.393f, 0.769f, 0.189f);
		float3 temp = dot(color.rgb, sepia);
		temp.r += 0.2;
		temp.g += 0.1;
		resultColor = float4(temp, color.a);
	}
	else if (_selection == 4)
	{
		// Negative
		float3 negative = 1 - abs(color.rgb);
		resultColor = float4(negative, color.a);
	}
	else if (_selection == 5)
	{
		// Posterize
		float3 value = float3(4.0f, 4.0f, 4.0f);
		float3 posterize = round(color.rgb * value) / value;
		resultColor = float4(posterize, color.a);
	}
	else
		resultColor = color;
	
	return resultColor;
}

/*
Semantic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����ϸ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

slot
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����
- �ֿ� ����
	1) ��� ���� ����
	- ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS���� ������ �� �ִ�
	- ��� ���� ������ register(b#)�� ����Ͽ� ����
	
	2) �ؽ�ó ����
	- �̹��� �����͸� �����ϴµ� ���
	- �ؽ�ó ���� ������ register(t#)�� ����Ͽ� ����

	3) ���÷� ����
	- �ؽ�ó�� ���ø� �ϴµ� ���
	- ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constant Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� �ִ�
- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�

Sampler : ���÷�
- �ؽ�ó���� �ȼ� ���� �������� ����� �����ϴ� ��ü
- �ؽ�ó ���ø��� �ؽ�ó �̹����� ���� �ؼ� ���� ����ϴ� �۾�
  (�ؼ� = �ؽ�ó�� �ȼ� ��)
*/