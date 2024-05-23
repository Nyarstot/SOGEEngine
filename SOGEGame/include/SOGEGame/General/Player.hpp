#ifndef PONG_PLAYER_HPP
#define PONG_PLAYER_HPP

#include "SOGEGame/General/Racket.hpp"
#include <SOGE/SOGE.hpp>

class Player
{
private:
    std::unique_ptr<Racket> mRacket;
    soge::Point2D mVelocity = { 0.0f, 0.0f };
    bool mIsMoving = false;
    float mSpeed = 1.0f;
    int mScore = 0;

public:
    Player();
    ~Player();

    void Update(float aDeltaTime);
    void OnEvent(soge::Event& aEvent);

    soge::Point3D GetTranslation() const { return mRacket->GetTranslation(); }
    Racket* GetRacket() const { return mRacket.get(); }

    void EncreaseScore() { mScore++; }
    int GetScore() const { return mScore; }

public:
    static std::shared_ptr<Player> CreateShared();
    static std::unique_ptr<Player> CreateUnique();

};

#endif // !PONG_PLAYER_HPP
