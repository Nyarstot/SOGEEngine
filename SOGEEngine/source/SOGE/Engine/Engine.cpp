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
        mWindow->SetEventCallback(std::bind(&Engine::OnEvent, this, std::placeholders::_1));
        mFPSCounter = FPSCounter::Create();

        // Init singleton classes

        mRenderer->Init(mWindow);
        mInputManager->Init(mWindow);
    }

    Engine::~Engine()
    {

    }

    void Engine::Run()
    {
        mWindow->Show();

        while (mIsRunning) {
            mFPSCounter->AddFrame();
            mRenderer->Render(mRenderLayerStack, mFPSCounter->GetDeltaTime());
            mWindow->OnUpdate();
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

    void Engine::OnEvent(Event& aEvent)
    {
        for (auto it = mRenderLayerStack.end(); it != mRenderLayerStack.begin();) {
            (*--it)->OnEvent(aEvent);
            if (aEvent.IsHandled()) {
                break;
            }
        }
    }
}
