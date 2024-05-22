#ifndef PONG_RACKET_HPP
#define PONG_RACKET_HPP

#include <SOGE/SOGE.hpp>

enum class RacketSide
{
    LEFT = 0x00,
    RIGHT = 0x00
};

class Racket : public soge::GameObject
{
private:
    RacketSide mSide = RacketSide::LEFT;

public:
    Racket(soge::Point3D aPosition);
    ~Racket();

    void Update(float aDeltaTime) override;
    soge::Point3D GetTranslation() const { return mObjectSprite->GetTranslation(); }

public:
    static std::shared_ptr<Racket> CreateShared(soge::Point3D aPosition);
    static std::unique_ptr<Racket> CreateUnique(soge::Point3D aPosition);

};

#endif // !PONG_RACKET_HPP
