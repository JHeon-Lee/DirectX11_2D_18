#include "Framework.h"
#include "Sounds.h"

Sounds::Sounds()
    : count(150), volume(1.0f)
{
    System_Create(&system);

    system->init(count, FMOD_INIT_NORMAL, NULL);

    sound = new Sound * [count];
    channel = new Channel * [count];

    ZeroMemory(sound, sizeof(Sound*) * count);
    ZeroMemory(channel, sizeof(Channel*) * count);
}

Sounds::~Sounds()
{
    if (channel != NULL)
    {
        for (uint i = 0; i < count; i++)
            if (channel[i]) channel[i]->stop();
    }

    if (sound != NULL)
    {
        for (uint i = 0; i < count; i++)
            if (sound[i]) sound[i]->release();
    } 

    SAFE_DELETE_ARRAY(channel);
    SAFE_DELETE_ARRAY(sound);

    if (system != NULL)
    {
        system->release();
        system->close();
    }

    sounds.clear();
}

void Sounds::Update()
{
    system->update();
}

void Sounds::AddSound(string name, wstring file, bool bLoop)
{
    if (bLoop == true)
        system->createStream(String::ToString(file).c_str(), FMOD_LOOP_NORMAL, NULL, &sound[sounds.size()]);
    else
        system->createStream(String::ToString(file).c_str(), FMOD_DEFAULT, NULL, &sound[sounds.size()]);

    sounds[name] = &sound[sounds.size()];
}

void Sounds::Play(string name, float volume)
{
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            system->playSound(*iter->second, NULL, false, &channel[count]);
            channel[count]->setVolume(volume);
        }
    }
}

void Sounds::Stop(string name)
{
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            channel[count]->stop();
            break;
        }
    }
}

void Sounds::Pause(string name)
{
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            channel[count]->setPaused(true);
            break;
        }
    }
}

void Sounds::Resume(string name)
{
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            channel[count]->setPaused(false);
            break;
        }
    }
}

bool Sounds::IsPlaying(string name)
{
    bool bPlay = false;
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            channel[count]->isPlaying(&bPlay);
            break;
        }
    }

    return bPlay;
}

bool Sounds::IsPauses(string name)
{
    bool bPaused = false;
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            channel[count]->getPaused(&bPaused);
            break;
        }
    }

    return bPaused;
}

void Sounds::SetVolume(string name, float volume)
{
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            channel[count]->setVolume(volume);
            break;
        }
    }
}

float Sounds::GetVolume(string name)
{
    float volume = 0.0f;
    int count = 0;
    iter = sounds.begin();

    for (iter; iter != sounds.end(); iter++, count++)
    {
        if (name == iter->first)
        {
            channel[count]->getVolume(&volume);
            break;
        }
    }

    return volume;
}

