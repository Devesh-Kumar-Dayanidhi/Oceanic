#pragma once

#include <SDL3/SDL.h>

namespace Oceanic
{

    class Application
    {
    public:
        Application();
    public:
        virtual void Start() {}
        virtual bool Flags() { return false; }
        virtual void OnUpdate(float dt) {}
        virtual void End() {}
    };

    extern Application* FetchApplication();

}