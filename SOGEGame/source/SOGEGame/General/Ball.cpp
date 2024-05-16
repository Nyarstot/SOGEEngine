#include "SOGEGame/General/Ball.hpp"


Ball::Ball()
    : GameObject({ 0.0f, 0.0f, 0.0f }, { 0.01f, 0.01f, 0.0f })
{
    SOGE_APP_INFO_LOG("app");
    mRandomizer = soge::Random();

    mBallState = BallState::READY;
    mSpeedIncrease = 0.01f;
    mInitialSpeed = 0.01f;
    mVelocity = {0.f, 0.f};

}

Ball::~Ball()
{

}

void Ball::Update(float aDeltaTime)
{
    mObjectSprite->Update(aDeltaTime);
    mObjectSprite->Draw();

    switch (mBallState)
    {
    case Ball::BallState::READY:
        this->Launch(mRandomizer.RandBool(), aDeltaTime);
        break;
    case Ball::BallState::LAUNCHED:
        mObjectSprite->Translate({ mVelocity.x, mVelocity.y, 0.0f});
        if (mObjectSprite->GetTranslation().x > 1.1f || mObjectSprite->GetTranslation().x < -1.1f
            || mObjectSprite->GetTranslation().y > 1.f || mObjectSprite->GetTranslation().y < -1.1f) {
            mBallState = BallState::OUTOFBOUND;
        }
        break;
    case Ball::BallState::OUTOFBOUND:
        SOGE_APP_INFO_LOG("Out of bound");
        this->Reset();
        mBallState = BallState::READY();
        break;
    case Ball::BallState::BOUNCED:
        break;
    default:
        break;
    }
}

void Ball::Launch(bool aLaunchSide, float aDeltaTime)
{
    // true - launch ball to the left side
    // false - launch ball to the right side

    if (aLaunchSide == true) {
        mVelocity.x -= mSpeedIncrease * aDeltaTime;
        launchedSide = true;
    }
    else {
        mVelocity.x += mSpeedIncrease * aDeltaTime;
        launchedSide = false;
    }

    mVelocity.y -= mRandomizer.RandDoubleNorm() * mSpeedIncrease * aDeltaTime;
    mBallState = BallState::LAUNCHED;
}

void Ball::Reset()
{
    this->MoveTo({ 0.0f, 0.0f, 0.0f });
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
