#pragma once

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