#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path, Pivot pivot)
    : position(position), size(size), rotation(rotation), pivot(pivot)
{
    SetVertices();

    vb = new VertexBuffer();
    vb->Create(vertices, D3D11_USAGE_DYNAMIC);

    indices = { 0,1,2,0,3,1 };
    ib = new IndexBuffer;
    ib->Create(indices, D3D11_USAGE_IMMUTABLE);

    vs = new VertexShader;
    vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

    ps = new PixelShader;
    ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

    il = new InputLayout;
    il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());

    wb = new WorldBuffer;

    HRESULT hr = D3DX11CreateShaderResourceViewFromFile
    (
        DEVICE,
        path.c_str(),
        nullptr,
        nullptr,
        &srv,
        nullptr
    );
    CHECK(hr);
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    SetVertices();

    vb = new VertexBuffer();
    vb->Create(vertices, D3D11_USAGE_DYNAMIC);

    indices = { 0,1,2,0,3,1 };
    ib = new IndexBuffer;
    ib->Create(indices, D3D11_USAGE_IMMUTABLE);

    vs = new VertexShader;
    vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

    ps = new PixelShader;
    ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

    il = new InputLayout;
    il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());

    wb = new WorldBuffer;
}

TextureRect::~TextureRect()
{
    SAFE_DELETE(wb);
    SAFE_DELETE(il);
    SAFE_DELETE(ps);
    SAFE_DELETE(vs);
    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void TextureRect::Update()
{
    UpdateWorld();
    Move();
}

void TextureRect::UpdateWorld()
{
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    D3DXMatrixRotationZ(&R, rotation);
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    world = S * R * T;
    wb->SetWorld(world);
}

void TextureRect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    ps->SetShader();
    wb->SetVSBuffer(0);

    DC->PSSetShaderResources(0, 1, &srv);

    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
}

void TextureRect::SetShader(wstring shaderPath)
{
    vs->Clear();
    ps->Clear();
    vs->Create(ShaderPath + shaderPath, "VS");
    ps->Create(ShaderPath + shaderPath, "PS");
}

void TextureRect::MapVertexBuffer()
{
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TextureRect::UnmapVertexBuffer()
{
    memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
    DC->Unmap(vb->GetResource(), 0);
}

void TextureRect::Move()
{
}

void TextureRect::SetVertices()
{
    vertices.assign(4, VertexTexture());

    switch (pivot)
    {
        case CENTER:
            vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
            vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
            vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
            vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
            break;
        case LEFT:
            vertices[0].position = Vector3(-0.0f, -0.5f, 0.0f);
            vertices[1].position = Vector3(+1.0f, +0.5f, 0.0f);
            vertices[2].position = Vector3(+1.0f, -0.5f, 0.0f);
            vertices[3].position = Vector3(-0.0f, +0.5f, 0.0f);
            break;
        case RIGHT:
            vertices[0].position = Vector3(-1.0f, -0.5f, 0.0f);
            vertices[1].position = Vector3(+0.0f, +0.5f, 0.0f);
            vertices[2].position = Vector3(+0.0f, -0.5f, 0.0f);
            vertices[3].position = Vector3(-1.0f, +0.5f, 0.0f);
            break;
        case UP:
            vertices[0].position = Vector3(-0.5f, -1.0f, 0.0f);
            vertices[1].position = Vector3(+0.5f, +0.0f, 0.0f);
            vertices[2].position = Vector3(+0.5f, -1.0f, 0.0f);
            vertices[3].position = Vector3(-0.5f, +0.0f, 0.0f);
            break;
        case DOWN:
            vertices[0].position = Vector3(-0.5f, -0.0f, 0.0f);
            vertices[1].position = Vector3(+0.5f, +1.0f, 0.0f);
            vertices[2].position = Vector3(+0.5f, -0.0f, 0.0f);
            vertices[3].position = Vector3(-0.5f, +1.0f, 0.0f);
            break;
    }

    vertices[0].uv = Vector2(0, 1);
    vertices[1].uv = Vector2(1, 0);
    vertices[2].uv = Vector2(1, 1);
    vertices[3].uv = Vector2(0, 0);
}
