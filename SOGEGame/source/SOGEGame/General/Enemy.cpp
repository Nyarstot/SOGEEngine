#include "SOGEGame/General/Enemy.hpp"

Enemy::Enemy()
{
    mRacket = Racket::CreateUnique({ 0.9f, 0.1f, 0.0f });
    mRacket->SetObjectName("enemyRacket");
    mSpeed = 0.07;
}

Enemy::~Enemy()
{
    mRacket.release();
}

void Enemy::Update(float aDeltaTime, Ball* aBall)
{
    mRacket->Update(aDeltaTime);
    mVelocity.y = 0.0f;

    auto selfBoundBox = mRacket->GetCollision()->GetBoundingBox();
    auto ballBoundBox = aBall->GetCollision()->GetBoundingBox();
    const auto difference = ballBoundBox.Center.y - selfBoundBox.Center.y;

    if (difference > selfBoundBox.Extents.y / 3) {
        mVelocity.y += mSpeed;
    }
    else if (difference < -selfBoundBox.Extents.y / 3) {
        mVelocity.y -= mSpeed;
    }

    mRacket->Translate({ 0.0f, mVelocity.y, 0.0f });
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
