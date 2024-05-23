#include <SOGE/SOGE.hpp>
#include <SOGE/Engine/EntryPoint.hpp>

class Game : public soge::Engine
{
public:
    Game()
    {

    }

    ~Game()
    {

    }

};

soge::Engine* soge::CreateApplication()
{
    return new Game();
}