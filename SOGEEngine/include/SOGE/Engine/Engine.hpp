#ifndef SOGE_ENGINE_HPP
#define SOGE_ENGINE_HPP

#include "SOGE/Containers/Layer.hpp"
#include "SOGE/Containers/LayerStack.hpp"
#include "SOGE/System/Window.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Engine/FPSCounter.hpp"
#include "SOGE/Event/Event.hpp"
#include "SOGE/Input/InputManager.hpp"

namespace soge
{

    class Engine
    {

    private:
        bool mIsRunning;
        LayerStack mRenderLayerStack;

        std::unique_ptr<Window> mWindow;
        std::unique_ptr<FPSCounter> mFPSCounter;

        // Singleton classes

        Renderer* mRenderer = Renderer::GetInstance();
        InputManager* mInputManager = InputManager::GetInstance();

    protected:
        static Engine& GetInstance();

    public:
        Engine();
        virtual ~Engine();

        void Run();
        void Shutdown();

        void PushRenderLayer(Layer* aRenderLayer);
        void PushRenderOverlay(Layer* aRenderOverlay);
        void OnEvent(Event& aEvent);

    };

    Engine* CreateApplication();
}


#endif // !SOGE_ENGINE_HPP
