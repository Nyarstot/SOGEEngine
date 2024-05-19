#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
    mPlayer = Player::CreateUnique();
    mBall = Ball::CreateUnique();
    mPlayer2Racket = soge::Sprite::Create({  0.9f, 0.0f }, { 0.01f, 0.2f });
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

    auto* physEngine = soge::PhysicsEngine::GetInstance();
    physEngine->CollisionTest(mPlayer->GetRacket()->GetCollision(), mBall->GetCollision());
}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    if (aEvent.GetEventType() == soge::EventTypes::GameplayEvents::eObjectCollided) {
        SOGE_APP_INFO_LOG("{0}", aEvent.ToString());
    }

    mPlayer->OnEvent(aEvent);
}
