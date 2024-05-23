#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
    mPlayer = Player::CreateUnique();
    mEnemy = Enemy::CreateUnique();
    mBall = Ball::CreateUnique();
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
    mEnemy->Update(aDeltaTime);
    mBall->Update(aDeltaTime);

    auto* physEngine = soge::PhysicsEngine::GetInstance();
    physEngine->CollisionTest(mPlayer->GetRacket()->GetCollision(), mBall->GetCollision());
    physEngine->CollisionTest(mEnemy->GetRacket()->GetCollision(), mBall->GetCollision());
}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    mPlayer->OnEvent(aEvent);
    mBall->OnEvent(aEvent);
}
