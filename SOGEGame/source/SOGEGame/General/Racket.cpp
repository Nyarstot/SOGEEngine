#include "SOGEGame/General/Racket.hpp"

Racket::Racket(RacketSide aRacketSide)
{
    mSide = aRacketSide;
    if (mSide == RacketSide::LEFT) {
        mRacketSprite = soge::Sprite::Create({ -0.9f, 0.0f }, { 0.01f, 0.2f });
    }
    else {
        mRacketSprite = soge::Sprite::Create({ 0.9f, 0.0f }, { 0.01f, 0.2f });
    }
}

Racket::~Racket()
{
    mRacketSprite.reset();
}

void Racket::Update(float aDeltaTime)
{
    mRacketSprite->Update(aDeltaTime);
    mRacketSprite->Draw();
}

void Racket::TranslateTo(float aYPos)
{
    mRacketSprite->Translate({ 0, aYPos, 0 });
}

std::shared_ptr<Racket> Racket::CreateShared(RacketSide aRacketSide)
{
    return std::make_shared<Racket>(aRacketSide);
}

std::unique_ptr<Racket> Racket::CreateUnique(RacketSide aRacketSide)
{
    return std::make_unique<Racket>(aRacketSide);
}
