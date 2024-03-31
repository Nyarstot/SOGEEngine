#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
}

MainGameLayer::~MainGameLayer()
{
}

void MainGameLayer::OnAttach()
{
    SOGE_APP_INFO_LOG("MainGameLayer attached");
}

void MainGameLayer::OnDetach()
{
}

void MainGameLayer::OnUpdate()
{
}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    auto input = soge::InputManager::GetInstance();
    if (input->IsKeyPressed(soge::Keys::A)) {
        SOGE_APP_INFO_LOG("{0}", aEvent.ToString());
    }
    else if (input->IsKeyPressed(soge::Keys::Z)) {
        SOGE_APP_INFO_LOG("{0}", aEvent.ToString());
    }
}
