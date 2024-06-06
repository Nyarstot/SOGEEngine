#ifndef SOGEGAME_MAIN_RENDER_LAYER_HPP
#define SOGEGAME_MAIN_RENDER_LAYER_HPP

#include <SOGE/SOGE.hpp>

class MainRenderLayer : public soge::Layer
{
private:
    std::unique_ptr<soge::Sprite> sprite = soge::Sprite::CreateUnique({ 0.0f, 0.0f }, { 0.1f, 0.1f });
    std::unique_ptr<soge::Primitive3DBox> box = soge::Primitive3DBox::CreateUnique({ 0.1f, 0.1f, 0.1f }, { 0.0f, 0.0f, 0.0f });

public:
    MainRenderLayer();
    virtual ~MainRenderLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float aDeltaTime) override;
    virtual void OnEvent(soge::Event& aEvent) override;

};

#endif // !SOGEGAME_MAIN_RENDER_LAYER_HPP
