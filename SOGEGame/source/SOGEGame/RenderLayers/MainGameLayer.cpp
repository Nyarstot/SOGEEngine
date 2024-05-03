#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
    mPlayer = Player::CreateUnique();
    mBall = Ball::CreateUnique();
    mPlayer2Racket = soge::Sprite::Create({  0.9f, 0.0f }, { 0.01f, 0.2f });
    //mPlayer1Racket = soge::Square::Create({ -0.9f, 0.0f }, { 0.01f, 0.2f });
    //mPlayer2Racket = soge::Square::Create({ 0.9f, 0.0f }, { 0.01f, 0.2f });
}

MainGameLayer::~MainGameLayer()
{
}

void MainGameLayer::OnAttach()
{

}

void MainGameLayer::OnDetach()
{
}

void MainGameLayer::OnUpdate(float aDeltaTime)
{
    //mPlayer1Racket->test(aDeltaTime);
    mPlayer->Update(aDeltaTime);
    mBall->Update(aDeltaTime);

    mPlayer2Racket->Update(aDeltaTime);
    mPlayer2Racket->Draw();

}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    mPlayer->OnEvent(aEvent);
}
