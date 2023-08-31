#include "stdafx.h"
#include "02_TextureDemo.h"

#include "Geometries/TextureRect.h"
//#include "Geometries/Diamond.h"

void TextureDemo::Init()
{
    tr = new TextureRect
    (
        Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0),
        Vector3(200, 200, 0), 0,
        TexturePath + L"images.jpg"
    );

    //d = new Diamond
    //(
    //    Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0),
    //    Vector3(500, 500, 0), 0,
    //    TexturePath + L"images.jpg"
    //);
}

void TextureDemo::Destroy()
{
    SAFE_DELETE(tr);
    //SAFE_DELETE(d);
}

void TextureDemo::Update()
{
    tr->Update();
    //d->Update();
}

void TextureDemo::Render()
{
    tr->Render();
    //d->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
}
