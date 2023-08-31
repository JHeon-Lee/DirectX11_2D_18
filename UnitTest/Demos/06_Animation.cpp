#include "stdafx.h"
#include "06_Animation.h"

#include "Geometries/AnimationRect.h"
#include "Geometries/Player.h"

void AnimationDemo::Init()
{
    player = new Player({ 720, 360, 0 }, { 200,200,0 });
    Sounds::Get()->AddSound("Music", SoundPath + L"popVirus.mp3");
    Sounds::Get()->Play("Music", 1.0f);
}

void AnimationDemo::Destroy()
{
    SAFE_DELETE(player);
}

void AnimationDemo::Update()
{
    player->Update();

    if (Keyboard::Get()->Down(VK_F2))
    {
        if(!Sounds::Get()->IsPauses("Music"))
            Sounds::Get()->Pause("Music");
        else
            Sounds::Get()->Resume("Music");
    }
    
}

void AnimationDemo::Render()
{
    player->Render();
}

void AnimationDemo::PostRender()
{
}

void AnimationDemo::GUI()
{
}

// Animator 리스트 초기화 안했고,
// frameSize 제대로 안썼고,
// texelStartPos.y Hegith->Width으로 적음