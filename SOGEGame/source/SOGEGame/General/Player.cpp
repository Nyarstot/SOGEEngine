#include "SOGEGame/General/Player.hpp"

Player::Player()
{
    mRacket = Racket::CreateUnique(RacketSide::LEFT);
}

Player::~Player()
{
    mRacket.release();
}

void Player::Update(float aDeltaTime)
{
    mRacket->Update(aDeltaTime);

    if (mSpeed != 0) {
        mRacket->TranslateTo(mVelocity.y * aDeltaTime);
    }
    SOGE_APP_INFO_LOG("Speed {0}", mSpeed);
    SOGE_APP_WARN_LOG("Velocity: {0}", mVelocity.y);
}

void Player::OnEvent(soge::Event& aEvent)
{
    auto input = soge::InputManager::GetInstance();

    // Press keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyPressed) {
        if (input->IsKeyPressed(soge::Keys::W)) {
            mVelocity.y += mSpeed * 0.04;
        }

        if (input->IsKeyPressed(soge::Keys::S)) {
            mVelocity.y -= mSpeed * 0.04;
        }
    }

    // Release keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyReleased) {

    }
}

std::shared_ptr<Player> Player::CreateShared()
{
    return std::make_shared<Player>();
}

std::unique_ptr<Player> Player::CreateUnique()
{
    return std::make_unique<Player>();
}
