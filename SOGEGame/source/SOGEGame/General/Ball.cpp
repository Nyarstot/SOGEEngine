#include "SOGEGame/General/Ball.hpp"

Ball::Ball()
    : GameObject({ 0.0f, 0.0f, 0.0f }, { 0.05f, 0.05f, 0.0f }, true)
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

    //SOGE_APP_INFO_LOG("{0}, {1}, {2}",
    //    mObjectSprite->GetTranslation().x,
    //    mObjectSprite->GetTranslation().y,
    //    mObjectSprite->GetTranslation().z);

    switch (mBallState)
    {
    case Ball::BallState::READY:
        this->Launch(mRandomizer.RandBool(), aDeltaTime);
        break;
    case Ball::BallState::LAUNCHED:
        this->Translate({ mVelocity.x, mVelocity.y, 0.0f });
        if (mObjectSprite->GetTranslation().x > 1.1f || mObjectSprite->GetTranslation().x < -1.1f
            || mObjectSprite->GetTranslation().y > 1.f || mObjectSprite->GetTranslation().y < -1.1f) {
            mOutOfBound = true;
            mBallState = BallState::OUTOFBOUND;
        }
        break;
    case Ball::BallState::OUTOFBOUND:
        this->Reset();

        if (mObjectSprite->GetTranslation().x > 0) {
            mOutOfBoundSide = false; // Bound to enemy
        }
        else if (mObjectSprite->GetTranslation().x < 0) {
            mOutOfBoundSide = true; // Bount to player
        }
        mBallState = BallState::READY();
        mOutOfBound = false;
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

float Ball::Clamp(float aX, float aUpper, float aBottom)
{
    return std::min(aUpper, std::max(aX, aBottom));
}

void Ball::ChangeColor(float r, float g, float b)
{
    mObjectSprite->ChangeColor(r, g, b);
    SOGE_APP_INFO_LOG("{0}.{1}.{2}", r, g, b);
}

void Ball::OnEvent(soge::Event& aEvent)
{
    if (aEvent.GetEventType() == soge::EventTypes::GameplayEvents::eObjectCollided) {
        auto collisionEvent = soge::StaticEventCast<soge::CollidedEvent>(aEvent);

        //if (collisionEvent.GetColliderObject1()->GetColliderName() == "playerRacket_collider") {
        //    mVelocity.y = -mVelocity.y;
        //    mVelocity.x = -mVelocity.x;
        //}

        //if (collisionEvent.GetColliderObject1()->GetColliderName() == "enemyRacket_collider") {
        //    mVelocity.y = abs(mVelocity.y);
        //    mVelocity.x = abs(mVelocity.x);
        //    SOGE_APP_INFO_LOG("COLLIDE");
        //}

        auto stickBoundBox = collisionEvent.GetColliderObject1()->GetBoundingBox();
        auto ballBoundBox = collisionEvent.GetColliderObject2()->GetBoundingBox();

        mVelocity.y = -mVelocity.y;
        mVelocity.x = -mVelocity.x;

        //mVelocity.x = mVelocity.x > 0 ? mSpeedIncrease : -mSpeedIncrease;
        mVelocity.x = -this->Clamp(-mVelocity.x, 3, -3);
        //SOGE_APP_INFO_LOG("TEST: {0}", mVelocity.x);
        if (std::abs(ballBoundBox.Center.x) + ballBoundBox.Extents.x >
            std::abs(stickBoundBox.Center.x) + stickBoundBox.Extents.x)
        {
            ballBoundBox.Center.x = (abs(stickBoundBox.Center.x) -
                stickBoundBox.Extents.x - stickBoundBox.Extents.y) *
                (ballBoundBox.Center.x > 0 ? 1 : -1);
        }

        auto x = this->GetSprite()->GetScaling().x;
        auto y = this->GetSprite()->GetScaling().y;
        auto z = this->GetSprite()->GetScaling().z;

        if (!(x <= 0.2f)) {
            this->Scale({ -0.1f, -0.1f, -0.1f });
        }

        this->ChangeColor(mRandomizer.RandDoubleNorm(), mRandomizer.RandDoubleNorm(), mRandomizer.RandDoubleNorm());

        //const auto ratio = (ballBoundBox.Center.y - stickBoundBox.Center.y) / abs(stickBoundBox.Extents.y);
        //mVelocity.y = -std::min(std::floor(ratio * 0.01f), 9.0f) / 100;
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
