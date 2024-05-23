#include "SOGEGame/General/Enemy.hpp"

Enemy::Enemy()
{
    mRacket = Racket::CreateUnique({ 0.9f, 0.1f, 0.0f });
    mRacket->SetObjectName("enemyRacket");
}

Enemy::~Enemy()
{
    mRacket.release();
}

void Enemy::Update(float aDeltaTime)
{
    mRacket->Update(aDeltaTime);

    if (mIsMoving) {
        mRacket->Translate({ 0.0f, mVelocity.y, 0.0f });
    }
}

void Enemy::OnEvent(soge::Event& aEvent)
{

}

std::shared_ptr<Enemy> Enemy::CreateShared()
{
    return std::make_shared<Enemy>();
}

std::unique_ptr<Enemy> Enemy::CreateUnique()
{
    return std::make_unique<Enemy>();
}
