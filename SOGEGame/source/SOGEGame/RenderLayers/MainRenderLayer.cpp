#include "SOGEGame/RenderLayers/MainRenderLayer.hpp"
#include <SOGE/SOGE.hpp>

MainRenderLayer::MainRenderLayer()
{

}

MainRenderLayer::~MainRenderLayer()
{

}

void MainRenderLayer::OnAttach()
{

}

void MainRenderLayer::OnDetach()
{

}

void MainRenderLayer::OnUpdate(float aDeltaTime)
{
    box->Draw();
    box->Update(aDeltaTime);

    sprite->Draw();
    sprite->Update(aDeltaTime);
    sprite->Rotate({aDeltaTime, aDeltaTime, aDeltaTime });

}

void MainRenderLayer::OnEvent(soge::Event& aEvent)
{

}
