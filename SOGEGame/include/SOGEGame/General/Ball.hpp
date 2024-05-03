#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <SOGE/SOGE.hpp>

class Ball
{
private:
    std::shared_ptr<soge::Sprite> mBallSprite;

public:
    Ball();
    ~Ball();

    void Update(float aDeltaTime);
    void OnEvent(soge::Event& aEvent);

};

#endif // !PONG_BALL_HPP
