#include "sogepch.hpp"
#include "SOGE/Graphics/SpriteFont.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    SpriteFont::SpriteFont(wchar_t const* aFontFilePath, bool aForceSRGB)
    {
        mFontDescriptor.fontFilePath    = aFontFilePath;
        mFontDescriptor.forceSRGB       = aFontFilePath;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        mDTKSpriteFont = std::make_unique<dx::SpriteFont>(device,
            mFontDescriptor.fontFilePath.c_str(), mFontDescriptor.forceSRGB);
    }

    SpriteFont::SpriteFont(SpriteFontDescription& aSpriteFontDesc)
    {
        mFontDescriptor = aSpriteFontDesc;
        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        mDTKSpriteFont = std::make_unique<dx::SpriteFont>(device,
            mFontDescriptor.fontFilePath.c_str(), mFontDescriptor.forceSRGB);
    }

    SpriteFont::~SpriteFont()
    {
        mDTKSpriteFont.release();
    }

    void SpriteFont::DrawString(SpriteBatch* aSpriteBatcher, wchar_t const* aText)
    {
        dx::SpriteBatch* spriteBatcher = aSpriteBatcher->GetNative();
        mDTKSpriteFont->DrawString(spriteBatcher, aText,
            mFontDescriptor.position, mFontDescriptor.color, mFontDescriptor.rotation);
    }

    // Static constructor callers

    std::shared_ptr<SpriteFont> SpriteFont::CreateShared(wchar_t const* aFontFilePath, bool aForceSRGB)
    {
        return std::make_shared<SpriteFont>(aFontFilePath, aForceSRGB);
    }

    std::unique_ptr<SpriteFont> SpriteFont::CreateUnique(wchar_t const* aFontFilePath, bool aForceSRGB)
    {
        return std::make_unique<SpriteFont>(aFontFilePath, aForceSRGB);
    }

    std::shared_ptr<SpriteFont> SpriteFont::CreateShared(SpriteFontDescription& aSpriteFontDesc)
    {
        return std::make_shared<SpriteFont>(aSpriteFontDesc);
    }

    std::unique_ptr<SpriteFont> SpriteFont::CreateUnique(SpriteFontDescription& aSpriteFontDesc)
    {
        return std::make_unique<SpriteFont>(aSpriteFontDesc);
    }
}