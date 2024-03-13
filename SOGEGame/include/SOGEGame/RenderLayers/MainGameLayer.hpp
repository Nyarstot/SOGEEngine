#ifndef SOGEGAME_MAIN_GAME_LAYER_HPP
#define SOGEGAME_MAIN_GAME_LAYER_HPP

#include <SOGE/SOGE.hpp>

class MainGameLayer : public soge::Layer
{
private:


public:
    MainGameLayer();
    ~MainGameLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;

};

#endif // !SOGEGAME_MAIN_GAME_LAYER_HPP
