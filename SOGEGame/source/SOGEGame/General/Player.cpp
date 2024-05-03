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
        mRacket->TranslateTo(mSpeed * aDeltaTime);
    }
}

void Player::OnEvent(soge::Event& aEvent)
{
    auto input = soge::InputManager::GetInstance();

    // Press keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyPressed) {
        if (input->IsKeyPressed(soge::Keys::W)) {
            mSpeed += 0.05f;
        }

        if (input->IsKeyPressed(soge::Keys::S)) {
            mSpeed -= 0.05f;
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
