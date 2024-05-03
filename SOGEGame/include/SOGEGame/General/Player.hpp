#ifndef PONG_PLAYER_HPP
#define PONG_PLAYER_HPP

#include "SOGEGame/General/Racket.hpp"
#include <SOGE/SOGE.hpp>

class Player
{
private:
    std::unique_ptr<Racket> mRacket;
    unsigned int mScore = 0;
    float mSpeed = 0.0f;
    float mVelocity = 0.0f;

public:
    Player();
    ~Player();

    void Update(float aDeltaTime);
    void OnEvent(soge::Event& aEvent);

    unsigned int GetScore() const { return mScore; }
    void SetScore(unsigned int aNewScore) { mScore = aNewScore; }

public:
    static std::shared_ptr<Player> CreateShared();
    static std::unique_ptr<Player> CreateUnique();

};

#endif // !PONG_PLAYER_HPP
