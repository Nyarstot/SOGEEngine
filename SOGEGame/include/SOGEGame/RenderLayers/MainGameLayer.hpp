#ifndef PONG_MAIN_GAME_LAYER_HPP
#define PONG_MAIN_GAME_LAYER_HPP

#include "SOGEGame/General/Player.hpp"
#include "SOGEGame/General/Enemy.hpp"
#include "SOGEGame/General/Ball.hpp"
#include <SOGE/SOGE.hpp>

class MainGameLayer : public soge::Layer
{
private:
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<Enemy> mEnemy;
    std::unique_ptr<Ball> mBall;

public:
    MainGameLayer();
    ~MainGameLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float aDeltaTime) override;
    virtual void OnEvent(soge::Event& aEvent) override;

};

#endif // !PONG_MAIN_GAME_LAYER_HPP
