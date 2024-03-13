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
