#include "SOGEGame/General/Ball.hpp"


Ball::Ball()
    : GameObject({ 0.0f, 0.0f, 0.0f }, { 0.01f, 0.01f, 0.0f })
{
    SOGE_APP_INFO_LOG("app");
    mRandomizer = soge::Random();

    mBallState = BallState::READY;
    mSpeedIncrease = 0.1f;
    mVelocity = {0.f, 0.f};

    this->SetObjectName("ballObject");
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
        this->Translate({ mVelocity.x, mVelocity.y, 0.0f });
        if (mObjectSprite->GetTranslation().x > 1.1f || mObjectSprite->GetTranslation().x < -1.1f
            || mObjectSprite->GetTranslation().y > 1.f || mObjectSprite->GetTranslation().y < -1.1f) {
            mBallState = BallState::OUTOFBOUND;
        }
        break;
    case Ball::BallState::OUTOFBOUND:
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

    float s = 2.f;
    mVelocity.y -= s * mSpeedIncrease * aDeltaTime;
    mVelocity.x -= s * mVelocity.x + 0.01;
    mBallState = BallState::LAUNCHED;
}

void Ball::Reset()
{
    this->Move({ 0.0f, 0.0f, 0.0f });
    mVelocity = { 0.0f, 0.0f };
}

void Ball::OnEvent(soge::Event& aEvent)
{
    if (aEvent.GetEventType() == soge::EventTypes::GameplayEvents::eObjectCollided) {
        auto collisionEvent = soge::StaticEventCast<soge::CollidedEvent>(aEvent);

        if (collisionEvent.GetColliderObject1()->GetColliderName() == "playerRacket_collider") {
            mVelocity.y = -mVelocity.y;
            mVelocity.x = -mVelocity.x;
        }

        if (collisionEvent.GetColliderObject1()->GetColliderName() == "enemyRacket_collider") {

        }
    }
}

std::shared_ptr<Ball> Ball::CreateShared()
{
    return std::make_shared<Ball>();
}

std::unique_ptr<Ball> Ball::CreateUnique()
{
    return std::make_unique<Ball>();
}
