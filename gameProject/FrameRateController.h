#pragma once
#include <SDL.h>

class FrameRateController
{
public:
    FrameRateController(int targetFPS) : m_TargetFPS(targetFPS), m_FrameDelay(1000 / targetFPS) {}

    void startFrame()
    {
        m_FrameStart = SDL_GetTicks();
    }

    void endFrame()
    {
        m_FrameTime = SDL_GetTicks() - m_FrameStart;
        if (m_FrameDelay > m_FrameTime)
        {
            SDL_Delay(m_FrameDelay - m_FrameTime);
        }
    }

private:
    int m_TargetFPS;
    int m_FrameDelay;
    Uint32 m_FrameStart;
    int m_FrameTime;
};
