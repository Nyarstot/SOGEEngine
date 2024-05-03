#ifndef PONG_MAIN_GAME_LAYER_HPP
#define PONG_MAIN_GAME_LAYER_HPP

#include "SOGEGame/General/Player.hpp"
#include "SOGEGame/General/Ball.hpp"
#include <SOGE/SOGE.hpp>

class MainGameLayer : public soge::Layer
{
private:
    //std::shared_ptr<soge::Square> mPlayer1Racket;
    //std::shared_ptr<soge::Square> mPlayer2Racket;
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<Ball> mBall;
    std::shared_ptr<soge::Sprite> mPlayer2Racket;

public:
    MainGameLayer();
    ~MainGameLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float aDeltaTime) override;
    virtual void OnEvent(soge::Event& aEvent) override;

};

#endif // !PONG_MAIN_GAME_LAYER_HPP
