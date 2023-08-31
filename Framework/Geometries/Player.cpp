#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
{
    animRect = new AnimationRect(position, size);
    animator = new Animator();

    Texture2D* srcTex = new Texture2D(TexturePath + L"jelda.png");
    Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

    Texture2D* runTex = new Texture2D(TexturePath + L"Run_R.png");
    
    AnimationClip* Run_R = new AnimationClip(L"RUN_R", runTex, 16, Vector2(0, 0), Vector2(runTex->GetWidth(), runTex->GetHeight()), 1.0f / 15.0f);
    animator->AddAnimClip(Run_R);

    AnimationClip* RunD = new AnimationClip
    (
        L"Run_D", srcTex, 10,
        Vector2(0, 0), Vector2(texSize.x, texSize.y * 0.25f),
        1.0f / 15.0f
    );

    AnimationClip* RunL = new AnimationClip
    (
        L"Run_L", srcTex, 10,
        Vector2(0, texSize.y * 0.25f), Vector2(texSize.x, texSize.y * 0.5f),
        1.0f / 15.0f
    );

    AnimationClip* RunU = new AnimationClip
    (
        L"Run_U", srcTex, 10,
        Vector2(0, texSize.y * 0.5f), Vector2(texSize.x, texSize.y * 0.75f),
        1.0f / 15.0f, true
    );

    AnimationClip* RunR = new AnimationClip
    (
        L"Run_R", srcTex, 10,
        Vector2(0, texSize.y * 0.75f), texSize,
        1.0f / 15.0f, true
    );

    animator->AddAnimClip(RunD);
    animator->AddAnimClip(RunL);
    animator->AddAnimClip(RunU);
    animator->AddAnimClip(RunR);
    //animator->SetCurrentAnimClip(L"Run_D");
    animator->SetCurrentAnimClip(L"RUN_R");

    animRect->SetAnimation(animator);

    SAFE_DELETE(srcTex);
}

Player::~Player()
{
    SAFE_DELETE(animator);
    SAFE_DELETE(animRect);
}

void Player::Update()
{
    animator->Update();
    Move();
    animRect->Update();
}

void Player::Render()
{
    animRect->Render();
}

void Player::Move()
{
    auto* key = Keyboard::Get();
    float delta = Time::Delta();
    Vector3 pos = animRect->GetPosition();

    if (key->Press('W') && key->Press('D'))
    {
        animRect->SetPosition(pos + Vector3(300 * delta, 200 * delta, 0));
        animator->SetCurrentAnimClip(L"Run_U");
    }
    else if (key->Press('W') && key->Press('A'))
    {
        animRect->SetPosition(pos + Vector3(-300 * delta, 200 * delta, 0));
        animator->SetCurrentAnimClip(L"Run_U");
    }
    else if (key->Press('S') && key->Press('D'))
    {
        animRect->SetPosition(pos + Vector3(300 * delta, -200 * delta, 0));
        animator->SetCurrentAnimClip(L"Run_D");
    }
    else if (key->Press('S') && key->Press('A'))
    {
        animRect->SetPosition(pos + Vector3(-300 * delta, -200 * delta, 0));
        animator->SetCurrentAnimClip(L"Run_D");
    }
    else if (key->Press('A'))
    {
        animRect->SetPosition(pos + Vector3(-300 * delta, 0, 0));
        animator->SetCurrentAnimClip(L"Run_L");
    }
    else if (key->Press('D'))
    {
        animRect->SetPosition(pos + Vector3(300 * delta, 0, 0));
        animator->SetCurrentAnimClip(L"Run_R");
    }

    else if (key->Press('W'))
    {
        animRect->SetPosition(pos + Vector3(0, 200 * delta, 0));
        animator->SetCurrentAnimClip(L"Run_U");
    }
    else if (key->Press('S'))
    {
        animRect->SetPosition(pos + Vector3(0, -200 * delta, 0));
        animator->SetCurrentAnimClip(L"Run_D");
    }
}
