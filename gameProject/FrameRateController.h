#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"
#include <string>
#include "AssetManager.h"
class FrameRateController
{
public:
    FrameRateController(int targetFPS) : m_TargetFPS(targetFPS), m_FrameDelay(1000 / targetFPS), m_FrameCount(0), m_ElapsedTime(0), m_FPS(0) {}

    void startFrame()
    {
        m_FrameStart = SDL_GetTicks();
    }

    void endFrame()
    {
        m_FrameTime = SDL_GetTicks() - m_FrameStart;
        if (m_FrameDelay > m_FrameTime)
        {
            m_FPS = m_TargetFPS;
            SDL_Delay(m_FrameDelay - m_FrameTime);
        }
        else {
            m_FPS = 1000 / m_FrameTime;
        }

        
    }

    int getFPS() const { return m_FPS; }

    void printFPS() {
        std::cout << m_FPS << std::endl;
    }

private:
    int m_TargetFPS;
    int m_FrameDelay;
    Uint32 m_FrameStart;
    int m_FrameTime;

    int m_FrameCount;
    Uint32 m_ElapsedTime;
    int m_FPS;
};