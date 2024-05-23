#include "sogepch.hpp"
#include "SOGE/Graphics/SpriteFont.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    SpriteFont::SpriteFont(wchar_t const* aFontFilePath, bool aForceSRGB)
    {
        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        mDTKSpriteFont = std::make_unique<dx::SpriteFont>(device, aFontFilePath, aForceSRGB);
    }

    SpriteFont::~SpriteFont()
    {
        mDTKSpriteFont.release();
    }

    void SpriteFont::DrawString(SpriteBatch* aSpriteBatch, wchar_t const* aText, BaseFontDesc aFontDesc)
    {
        mDTKSpriteFont->DrawString(aSpriteBatch->GetNative(), aText, aFontDesc.position, aFontDesc.color, aFontDesc.rotation);
    }

    std::shared_ptr<SpriteFont> SpriteFont::CreateShared(wchar_t const* aFontFilePath, bool aForceSRGB)
    {
        return std::make_shared<SpriteFont>(aFontFilePath, aForceSRGB);
    }

    std::unique_ptr<SpriteFont> SpriteFont::CreateUnique(wchar_t const* aFontFilePath, bool aForceSRGB)
    {
        return std::make_unique<SpriteFont>(aFontFilePath, aForceSRGB);
    }
}