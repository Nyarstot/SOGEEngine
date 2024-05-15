#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <SOGE/SOGE.hpp>

class Ball
{
    enum class BallState
    {
        READY = 0x00,
        LAUNCHED = 0x01,
        OUTOFBOUND = 0x02
    };

private:
    std::shared_ptr<soge::Sprite> mBallSprite;
    BallState mBallState;
    soge::Point2D mVelocity;
    float mInitialSpeed;
    float mSpeedIncrese;

private:
    void Launch(bool aLaunchSide);

public:
    Ball();
    ~Ball();

    void Update(float aDeltaTime);
    void OnEvent(soge::Event& aEvent);

public:
    static std::shared_ptr<Ball> CreateShared();
    static std::unique_ptr<Ball> CreateUnique();

};

#endif // !PONG_BALL_HPP
