#ifndef PONG_ENEMY_HPP
#define PONG_ENEMY_HPP

#include "SOGEGame/General/Racket.hpp"
#include <SOGE/SOGE.hpp>

class Enemy
{
private:
    std::unique_ptr<Racket> mRacket;
    soge::Point2D mVelocity = { 0.0f, 0.0f };
    bool mIsMoving = false;
    float mSpeed = 1.0f;

public:
    Enemy();
    ~Enemy();

    void Update(float aDeltaTime);
    void OnEvent(soge::Event& aEvent);

    soge::Point3D GetTranslation() const { return mRacket->GetTranslation(); }
    Racket* GetRacket() const { return mRacket.get(); }

public:
    static std::shared_ptr<Enemy> CreateShared();
    static std::unique_ptr<Enemy> CreateUnique();

};

#endif // !PONG_ENEMY_HPP
