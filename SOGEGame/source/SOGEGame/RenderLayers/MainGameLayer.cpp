#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
    mPlayer1Racket = soge::Square::Create({ -0.9f, 0.0f }, { 0.01f, 0.2f });
    mPlayer2Racket = soge::Square::Create({  0.9f, 0.0f }, { 0.01f, 0.2f });
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
    mPlayer1Racket->test(aDeltaTime);
    mPlayer1Racket->Draw();
    mPlayer2Racket->Draw();
}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    auto input = soge::InputManager::GetInstance();

    // Press keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyPressed) {
        if (input->IsKeyPressed(soge::Keys::W)) {
            SOGE_APP_INFO_LOG("W PRES");
        }
    }

    // Release keys events
    if (aEvent.GetEventType() == soge::EventTypes::InputEvents::eKeyReleased) {

    }
}
