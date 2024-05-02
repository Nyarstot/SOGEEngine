#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
    mPlayer1Racket = soge::Sprite::Create({ -0.9f, 0.0f }, { 0.01f, 0.2f });
    mPlayer2Racket = soge::Sprite::Create({  0.9f, 0.0f }, { 0.01f, 0.2f });
}

MainGameLayer::~MainGameLayer()
{
}

void MainGameLayer::OnAttach()
{

}

void MainGameLayer::OnDetach()
{
}

void MainGameLayer::OnUpdate(float aDeltaTime)
{
    //mPlayer1Racket->test(aDeltaTime);
    mPlayer1Racket->Update(aDeltaTime);
    mPlayer1Racket->Draw();
    mPlayer2Racket->Draw();

    if (speed != 0) {
        mPlayer1Racket->Translate({ 0, speed * aDeltaTime, 0 });
    }
}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    auto input = soge::InputManager::GetInstance();

    // Press keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyPressed) {
        if (input->IsKeyPressed(soge::Keys::W)) {
            //mPlayer1Racket->Translate({0.0f, 0.1f, 0.0f});
            speed += 0.05f;
        }

        if (input->IsKeyPressed(soge::Keys::S)) {
            //mPlayer1Racket->Translate({ 0.0f, -0.1f, 0.0f });
            speed -= 0.05f;
        }
    }

    // Release keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyReleased) {

    }
}
