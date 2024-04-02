#ifndef SOGEGAME_MAIN_GAME_LAYER_HPP
#define SOGEGAME_MAIN_GAME_LAYER_HPP

#include <SOGE/SOGE.hpp>

class MainGameLayer : public soge::Layer
{
private:
    std::shared_ptr<soge::Square> mPlayer1Racket;
    std::shared_ptr<soge::Square> mPlayer2Racket;

public:
    MainGameLayer();
    ~MainGameLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float aDeltaTime) override;
    virtual void OnEvent(soge::Event& aEvent) override;

};

#endif // !SOGEGAME_MAIN_GAME_LAYER_HPP
