#ifndef PONG_RACKET_HPP
#define PONG_RACKET_HPP

#include <SOGE/SOGE.hpp>

enum class RacketSide
{
    LEFT = 0x00,
    RIGHT = 0x00
};

class Racket
{
private:
    std::shared_ptr<soge::Sprite> mRacketSprite;
    RacketSide mSide = RacketSide::LEFT;

public:
    Racket(RacketSide aRacketSide);
    ~Racket();

    void Update(float aDeltaTime);
    void TranslateTo(float aYPos);

public:
    static std::shared_ptr<Racket> CreateShared(RacketSide aRacketSide);
    static std::unique_ptr<Racket> CreateUnique(RacketSide aRacketSide);

};

#endif // !PONG_RACKET_HPP
