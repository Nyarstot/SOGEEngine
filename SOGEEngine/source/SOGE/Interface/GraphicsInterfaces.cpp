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

    void IDrawable::AddBindable(BindableUniqePtr aBindablePtr) noexcept(!SOGE_DEBUG)
    {
        assert("You must use AddIndexBuffer to bind index buffer" && typeid(*aBindablePtr) != typeid(IndexBuffer));
        mBindables.push_back(std::move(aBindablePtr));
    }

    void IDrawable::AddIndexBuffer(std::unique_ptr<IndexBuffer>& aIndexBuffer) noexcept
    {
        assert("Attempting to add index buffer a second time" && mIndexBuffer == nullptr);
        mIndexBuffer = aIndexBuffer.get();
        mBindables.push_back(std::move(aIndexBuffer));
    }
}