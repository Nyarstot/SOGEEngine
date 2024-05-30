#include "sogepch.hpp"
#include "SOGE/Interface/GraphicsInterfaces.hpp"
#include "SOGE/Graphics/Bindable/IndexBuffer.hpp"


namespace soge
{
    void IDrawable::Draw() const noexcept(!SOGE_DEBUG)
    {
        for (auto& bindable : mBindables) {
            bindable->Bind();
        }
        // Drawindexd
    }

    void IDrawable::AddBindable(const IBindable& aBindable) noexcept(!SOGE_DEBUG)
    {

    }

    void IDrawable::AddIndexBuffer(const IndexBuffer& aIndexBuffer) noexcept
    {
    }
}