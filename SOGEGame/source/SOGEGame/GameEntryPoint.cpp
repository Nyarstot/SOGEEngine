#include <SOGE/SOGE.hpp>
#include <SOGE/Engine/EntryPoint.hpp>
#include "SOGEGame/RenderLayers/MainRenderLayer.hpp"

class Game : public soge::Engine
{
public:
    Game()
    {
        PushRenderLayer(new MainRenderLayer());
    }

    ~Game()
    {

    }

};

soge::Engine* soge::CreateApplication()
{
    return new Game();
}