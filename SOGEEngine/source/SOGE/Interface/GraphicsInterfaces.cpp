#include "sogepch.hpp"
#include "SOGE/Interface/GraphicsInterfaces.hpp"
#include "SOGE/Graphics/Bindable/IndexBuffer.hpp"
#include "SOGE/Graphics/Renderer.hpp"


namespace soge
{
    void IDrawable::Draw() const noexcept(!SOGE_DEBUG)
    {
        for (auto& bindable : mBindables) {
            bindable->Bind();
        }
        Renderer::GetInstance()->DrawIndexed(mIndexBuffer->GetIndicesCount());
    }

    void IDrawable::AddBindable(IBindable* aBindable) noexcept(!SOGE_DEBUG)
    {
        assert("You must use AddIndexBuffer to bind index buffer" && typeid(*aBindable) != typeid(IndexBuffer));
        mBindables.push_back(std::move(aBindable));
    }

    void IDrawable::AddIndexBuffer(IndexBuffer* aIndexBuffer) noexcept
    {
        if (mIndexBuffer == nullptr) {
            SOGE_INFO_LOG("Eban");
        }
        assert("Attempting to add index buffer a second time" && mIndexBuffer == nullptr);
        mIndexBuffer = std::make_unique<IndexBuffer>(*aIndexBuffer);
        mBindables.push_back(std::move(aIndexBuffer));
    }
}