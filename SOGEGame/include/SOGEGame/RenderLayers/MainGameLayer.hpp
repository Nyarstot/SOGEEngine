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

    std::unique_ptr<soge::SpriteFont> mPlayerCounter;
    std::unique_ptr<soge::SpriteFont> mEnemyCounter;
    std::unique_ptr<soge::CircleSprite> mCircle;

    soge::SpriteFontDescription mEnemyFontDescriptor;
    soge::SpriteFontDescription mPlayerFontDescriptor;

    std::wstring mGraphicsPlayerScore = L"0";
    std::wstring mGraphicsEnemyScore = L"0";

    std::unique_ptr<soge::SpriteBatch> mFontBatcher;
    soge::SpriteBatchDescriptor mFontBatcherDescriptor;

protected:
    void UpdateScore(bool aSide);

public:
    MainGameLayer();
    ~MainGameLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float aDeltaTime) override;
    virtual void OnEvent(soge::Event& aEvent) override;

};

#endif // !PONG_MAIN_GAME_LAYER_HPP
