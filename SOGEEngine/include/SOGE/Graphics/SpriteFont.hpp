#ifndef SOGE_SPRITE_FONT_HPP
#define SOGE_SPRITE_FONT_HPP

#include "SOGE/Containers/Simple.hpp"
#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Graphics/SpriteBatch.hpp"
#include <SpriteFont.h> // DirectXTK SpriteFont

namespace soge
{
    struct SpriteFontDescription
    {
        std::wstring fontFilePath   = L"";
        dx::XMVECTOR position       = { 0.0f, 0.0f };
        dx::XMVECTORF32 color       = dx::Colors::White;
        float rotation              = 0.0f;
        bool forceSRGB              = false;

        void ReplaceWith(SpriteFontDescription& aOther) {
            this->fontFilePath  = std::move(aOther.fontFilePath);
            this->position      = std::move(aOther.position);
            this->color         = std::move(aOther.color);
            this->rotation      = std::move(aOther.rotation);
            this->forceSRGB     = std::move(aOther.forceSRGB);
        }

        void operator= (SpriteFontDescription& aOther) {
            this->fontFilePath  = aOther.fontFilePath;
            this->position      = aOther.position;
            this->color         = aOther.color;
            this->rotation      = aOther.rotation;
            this->forceSRGB     = aOther.forceSRGB;
        }
    };

    class SpriteFont
    {
    private:
        std::unique_ptr<dx::SpriteFont> mDTKSpriteFont;
        SpriteFontDescription mFontDescriptor;

    public:
        SpriteFont(wchar_t const* aFontFilePath, bool aForceSRGB = false);
        SpriteFont(SpriteFontDescription& aSpriteFontDesc);
        ~SpriteFont();

        void DrawString(SpriteBatch* aSpriteBatcher,wchar_t const* aText);

        void SetFontColor(const dx::XMVECTORF32& aColor) { mFontDescriptor.color = aColor; }
        dx::XMVECTORF32 GetColor() const { return mFontDescriptor.color; }

    public:
        static std::shared_ptr<SpriteFont> CreateShared(wchar_t const* aFontFilePath, bool aForceSRGB = false);
        static std::unique_ptr<SpriteFont> CreateUnique(wchar_t const* aFontFilePath, bool aForceSRGB = false);

        static std::shared_ptr<SpriteFont> CreateShared(SpriteFontDescription& aSpriteFontDesc);
        static std::unique_ptr<SpriteFont> CreateUnique(SpriteFontDescription& aSpriteFontDesc);

    };
}

#endif // !SOGE_SPRITE_FONT_HPP
