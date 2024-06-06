#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <SOGE/SOGE.hpp>

class Ball : public soge::GameObject
{
    enum class BallState
    {
        READY = 0x00,
        LAUNCHED = 0x01,
        OUTOFBOUND = 0x02,
        BOUNCED = 0x03
    };

private:
    BallState mBallState;
    soge::Random mRandomizer;
    bool launchedSide;
    bool mOutOfBoundSide;
    bool mOutOfBound = false;

    soge::Point2D mVelocity;
    float mInitialSpeed;
    float mSpeedIncrease;

private:
    void Launch(bool aLaunchSide, float aDeltaTime);
    void Reset();

    float Clamp(float aX, float aUpper, float aBottom);
    void ChangeColor(float r, float g, float b);

public:
    Ball();
    ~Ball();

    bool IsOutOfBound() const { return mOutOfBound; }
    bool GetLastBound() const { return mOutOfBoundSide; }
    void Update(float aDeltaTime) override;
    void OnEvent(soge::Event& aEvent);

public:
    static std::shared_ptr<Ball> CreateShared();
    static std::unique_ptr<Ball> CreateUnique();

};

#endif // !PONG_BALL_HPP
