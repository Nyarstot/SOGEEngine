#include "SOGEGame/General/Racket.hpp"

Racket::Racket(soge::Point3D aPosition)
    : GameObject(aPosition, { 0.01f, 0.2f, 0.0f })
{

}

Racket::~Racket()
{

}

void Racket::Update(float aDeltaTime)
{
    mObjectSprite->Update(aDeltaTime);
    mObjectSprite->Draw();
}

void Racket::TranslateTo(float aYPos)
{
    mObjectSprite->Translate({ 0, aYPos, 0 });
}

void Racket::Move(float aYPos)
{
    mObjectSprite->Move({ 0.0f, aYPos, 0.0f });
}

std::shared_ptr<Racket> Racket::CreateShared(soge::Point3D aPosition)
{
    return std::make_shared<Racket>(aPosition);
}

std::unique_ptr<Racket> Racket::CreateUnique(soge::Point3D aPosition)
{
    return std::make_unique<Racket>(aPosition);
}
