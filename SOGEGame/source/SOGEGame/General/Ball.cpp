#include "SOGEGame/General/Ball.hpp"


Ball::Ball()
{
    SOGE_APP_INFO_LOG("app");
    soge::Random randomizer;
    double randomPosY = randomizer.RandDoubleNorm();

    mBallSprite = soge::Sprite::Create({0.0f, (float)randomPosY}, {0.01f, 0.01f});
    mBallState = BallState::READY;
    mSpeedIncrese = 0.0f;
    mInitialSpeed = 0.0f;
    mVelocity = {0.f, 0.f};

}

Ball::~Ball()
{
    mBallSprite.reset();
}

void Ball::Update(float aDeltaTime)
{
    mBallSprite->Update(aDeltaTime);
    mBallSprite->Draw();

    switch (mBallState)
    {
    case Ball::BallState::READY:
        break;
    case Ball::BallState::LAUNCHED:
        break;
    case Ball::BallState::OUTOFBOUND:
        break;
    default:
        break;
    }
}

void Ball::Launch(bool aLaunchSide)
{
    // true - launch ball to the left side
    // false - launch ball to the right side

    if (aLaunchSide == true) {

    }
}

void Ball::OnEvent(soge::Event& aEvent)
{

}

std::shared_ptr<Ball> Ball::CreateShared()
{
    return std::make_shared<Ball>();
}

std::unique_ptr<Ball> Ball::CreateUnique()
{
    return std::make_unique<Ball>();
}
