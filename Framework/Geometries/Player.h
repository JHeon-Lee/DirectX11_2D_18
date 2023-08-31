#pragma once

#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class Player
{
public:
    Player(Vector3 position, Vector3 size);
    ~Player();

    void Update();
    void Render();

    void Move();

private:
    AnimationRect* animRect = nullptr;
    Animator* animator = nullptr;
};