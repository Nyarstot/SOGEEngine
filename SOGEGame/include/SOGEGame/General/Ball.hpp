#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <SOGE/SOGE.hpp>

class Ball
{
private:
    std::shared_ptr<soge::Sprite> mBallSprite;
    float dx;
    float dy;


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
