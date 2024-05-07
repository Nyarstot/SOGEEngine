#include "SOGEGame/General/Ball.hpp"

Ball::Ball()
{
    SOGE_APP_INFO_LOG("app");
    soge::Random randomizer;
    double randomPosY = randomizer.RandDoubleNorm();

    mBallSprite = soge::Sprite::Create({0.0f, (float)randomPosY}, {0.01f, 0.01f});
}

Ball::~Ball()
{
    mBallSprite.reset();
}

void Ball::Update(float aDeltaTime)
{
    mBallSprite->Update(aDeltaTime);
    mBallSprite->Draw();
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
