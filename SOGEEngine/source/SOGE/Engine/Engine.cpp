#include "sogepch.hpp"
#include "SOGE/Engine/Engine.hpp"

namespace soge
{
    Engine& Engine::GetInstance()
    {
        static Engine sInstance;
        return sInstance;
    }

    Engine::Engine()
    {
        SOGE_INFO_LOG("Starting engine...");

        mWindow = Window::Create({ 1280, 720, L"CoolGame" });

        // Init singleton classes

        mRenderer->Init(mWindow);
    }

    Engine::~Engine()
    {

    }

    void Engine::Run()
    {
        mWindow->Show();

        while (mIsRunning) {
            mWindow->OnUpdate();
            mRenderer->Render();
        }
    }

    void Engine::Shutdown()
    {
    }

    void Engine::PushRenderLayer(Layer* aRenderLayer)
    {
        mRenderLayerStack.PushLayer(aRenderLayer);
        aRenderLayer->OnAttach();
    }

    void Engine::PushRenderOverlay(Layer* aRenderOverlay)
    {
        mRenderLayerStack.PushOverlay(aRenderOverlay);
        aRenderOverlay->OnAttach();
    }
}
