#pragma once

class RenderTexture
{
public:
    RenderTexture();
    ~RenderTexture();

    void RenderToTexture();
    ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
    ID3D11Texture2D* texture = nullptr;
    ID3D11RenderTargetView* rtv = nullptr;
    ID3D11ShaderResourceView* srv = nullptr;
};

/*
ī�޶� ���� ������ �����ϴ� �ʸ����� ������ ��
Texture2D = �ʸ� 
    -> ī�޶� ���� ������ ����Ǵ� ��

RTV = �ʸ��� ī�޶� ����
    -> RTV�� ����ϸ� ������ ����� �ش� RTV�� �����ϴ� �ؽ�ó�� ����

SRV = �ʸ��� ��ȭ�⿡ ���� 
    -> SRV�� ����ϸ� ���̴����� �ش� SRV�� �����ϴ� �ؽ�ó�� �����͸� ���� �� ����
*/