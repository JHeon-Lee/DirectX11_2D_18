#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    vertices.assign(4, VertexColor());

    vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
    vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
    vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
    vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);

    for (auto& v : vertices)
        v.color = color;

    vb = new VertexBuffer();
    vb->Create(vertices, D3D11_USAGE_DYNAMIC);

    indices = { 0,1,2,0,3,1 };
    ib = new IndexBuffer();
    ib->Create(indices, D3D11_USAGE_IMMUTABLE);

    vs = new VertexShader();
    vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");

    il = new InputLayout();
    il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());

    ps = new PixelShader();
    ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");

    wb = new WorldBuffer();

    box = new BoundingBox(position, size, rotation, Color(1, 0, 0, 1), CENTER);
}

Rect::~Rect()
{
    SAFE_DELETE(wb);
    SAFE_DELETE(ps);
    SAFE_DELETE(il);
    SAFE_DELETE(vs);
    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void Rect::Update()
{
    // Size
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    // Rotation
    D3DXMatrixRotationZ(&R, rotation);
    // Translation (position)
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    world = S * R * T;
    wb->SetWorld(world);

    box->Update(position, size, rotation);
}

void Rect::Render()
{
    // IA
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // VS
    vs->SetShader();
    wb->SetVSBuffer(0);

    // PS
    ps->SetShader();

    // OM
    DC->DrawIndexed(ib->GetCount(), 0, 0);

    //box->Render();
}

void Rect::GUI()
{
    using namespace ImGui;
    Begin("Rect");
    {
        InputFloat3("Pos", position, 2);
        InputFloat3("Size", size, 2);
        SliderAngle("Rot", &rotation, 0, 360.0f);

        if (ColorPicker4("Color", color))
            UpdateColor();
    }
    End();
}

void Rect::SetColor(Color color)
{
    this->color = color;
    UpdateColor();
}

void Rect::Move()
{
    auto key = Keyboard::Get();
    float delta = Time::Delta();

    if (key->Press('W'))
        position.y += 100 * delta;
    if (key->Press('S'))
        position.y -= 100 * delta;
    if (key ->Press('A'))
        position.x -= 100 * delta;
    if (key->Press('D'))
        position.x += 100 * delta;
}

void Rect::UpdateColor()
{
    D3D11_MAPPED_SUBRESOURCE subResource;
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    {
        for (auto& v : vertices)
            v.color = color;

        memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
    }
    DC->Unmap(vb->GetResource(), 0);
}