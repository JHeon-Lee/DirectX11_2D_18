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
카메라가 찍은 사진을 저장하는 필름같은 역할을 함
Texture2D = 필름 
    -> 카메라가 찍은 사직이 저장되는 곳

RTV = 필름을 카메라에 장착
    -> RTV를 사용하면 렌더링 결과가 해당 RTV가 참조하는 텍스처에 저장

SRV = 필름을 인화기에 장착 
    -> SRV를 사용하면 셰이더에서 해당 SRV가 참조하는 텍스처의 데이터를 읽을 수 있음
*/