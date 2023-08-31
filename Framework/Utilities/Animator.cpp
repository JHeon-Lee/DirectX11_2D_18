#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, float playRate, bool bResversed)
    : clipName(clipName), frameCount(frameCount), playRate(playRate), bReversed(bResversed)
{
    srv = srcTex->GetSRV();

    float imageWidth = srcTex->GetWidth();
    float imageHeight = srcTex->GetHeight();

    Vector2 clipSize = endPos - startPos;

    Vector2 frameSize;
    frameSize.x = clipSize.x / frameCount;
    frameSize.y = clipSize.y;

    texelFrameSize.x = frameSize.x / imageWidth;
    texelFrameSize.y = frameSize.y / imageHeight;

    Vector2 texelStartPos;
    texelStartPos.x = startPos.x / imageWidth;
    texelStartPos.y = startPos.y / imageHeight;

    Vector2 keyframe;

    for (uint i = 0; i < frameCount; i++)
    {
        keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
        keyframe.y = texelStartPos.y;

        keyFrames.push_back(keyframe);
    }
}

Animator::Animator()
{
}

Animator::~Animator()
{
    for (auto clip : animClips)
        SAFE_DELETE(clip.second);
}

void Animator::Update()
{
    if (deltaTime > currentClip->playRate)
    {
        if (currentClip->bReversed == false)
        {
            currentFrameIndex++;

            if (currentFrameIndex == currentClip->frameCount)
                currentFrameIndex = 0;

            currentFrame = currentClip->keyFrames[currentFrameIndex];
        }
        else
        {
            currentFrameIndex--;

            if (currentFrameIndex == -1)
                currentFrameIndex = currentClip->frameCount - 1;

            currentFrame = currentClip->keyFrames[currentFrameIndex];
        }
        deltaTime = 0.0f;
    }
    else
        deltaTime += Time::Delta();
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
    animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
    if (currentClip == nullptr && CheckExist(clipName) == true)
        currentClip = animClips.find(clipName)->second;
    else if (currentClip != nullptr && currentClip->clipName == clipName)
        return;

    if (CheckExist(clipName))
    {
        currentClip = animClips.find(clipName)->second;
        deltaTime = 0.0f;

        if (currentClip->bReversed == true)
            currentFrameIndex = currentClip->frameCount - 1;
        else
            currentFrameIndex = 0;

        currentFrame = currentClip->keyFrames[currentFrameIndex];
    }
}
