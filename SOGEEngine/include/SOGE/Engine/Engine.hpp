#ifndef SOGE_ENGINE_HPP
#define SOGE_ENGINE_HPP

#include "SOGE/Containers/Layer.hpp"
#include "SOGE/Containers/LayerStack.hpp"
#include "SOGE/System/Window.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Engine/FPSCounter.hpp"

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

    protected:
        static Engine& GetInstance();

    public:
        Engine();
        virtual ~Engine();

        void Run();
        void Shutdown();

        void PushRenderLayer(Layer* aRenderLayer);
        void PushRenderOverlay(Layer* aRenderOverlay);

    };

    Engine* CreateApplication();
}


#endif // !SOGE_ENGINE_HPP
