#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

#include <SOGE/SOGE.hpp>
#include <SOGE/Engine/EntryPoint.hpp>

class Game : public soge::Engine
{
public:
    Game()
    {
        PushRenderLayer(new MainGameLayer());
    }

    ~Game()
    {

    }

};

soge::Engine* soge::CreateApplication()
{
    return new Game();
}