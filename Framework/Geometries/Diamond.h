#pragma once

class Diamond
{
public:
    enum Pivot
    {
        CENTER = 0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

public:
    Diamond(Vector3 position, Vector3 size, float rotation, wstring path, Pivot pivot = CENTER);
    virtual ~Diamond();

    void Update();
    void Render();
    void GUI();

    void SetShader(wstring shaderPath);

private:
    void SetVertices();
    void UpdateWorld();

protected:
    vector<VertexTexture> vertices;
    VertexBuffer* vb = nullptr;

    vector<uint> indices;
    IndexBuffer* ib = nullptr;

    InputLayout* il = nullptr;

    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    Matrix world, S, R, T;

    WorldBuffer* wb = nullptr;

    Vector3 position;
    Vector3 size;
    float rotation;

    Pivot pivot;

    ID3D11ShaderResourceView* srv = nullptr;
};