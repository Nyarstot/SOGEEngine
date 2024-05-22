#include "SOGEGame/General/Player.hpp"

Player::Player()
{
    mRacket = Racket::CreateUnique({ -0.9f, 0.0f, 0.0f });
    mRacket->GetCollision()->SetName("PlayerCollision");
}

Player::~Player()
{
    mRacket.release();
}

void Player::Update(float aDeltaTime)
{
    mRacket->Update(aDeltaTime);

    if (mIsMoving) {
        mRacket->TranslateTo(mVelocity.y);
    }
    //SOGE_APP_INFO_LOG("Position: {0}", mRacket->GetTranslation().y);
}

void Player::OnEvent(soge::Event& aEvent)
{
    auto input = soge::InputManager::GetInstance();

    // Press keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyPressed) {
        if (input->IsKeyPressed(soge::Keys::W)) {
            mVelocity.y += 0.1f;
            mIsMoving = true;
        }

        if (input->IsKeyPressed(soge::Keys::S)) {
            mVelocity.y -= 0.1;
            mIsMoving = true;
        }
    }

    // Release keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyReleased) {
        if (input->IsKeyReleased(soge::Keys::W) || input->IsKeyReleased(soge::Keys::S)) {
            mIsMoving = false;
            mVelocity.y = 0;
        }
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
