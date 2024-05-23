#ifndef SOGE_SPRITE_FONT_HPP
#define SOGE_SPRITE_FONT_HPP

#include "SOGE/Containers/Simple.hpp"
#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Graphics/SpriteBatch.hpp"
#include <SpriteFont.h> // DirectXTK SpriteFont

namespace soge
{
    struct BaseFontDesc
    {
        dx::XMVECTOR position = { 0.0f, 0.0f };
        dx::XMVECTORF32 color = dx::Colors::White;
        float rotation = 0.0f;
    };

    class SpriteFont
    {
    private:
        std::unique_ptr<dx::SpriteFont> mDTKSpriteFont;

    public:
        SpriteFont(wchar_t const* aFontFilePath, bool aForceSRGB = false);
        ~SpriteFont();

        void DrawString(SpriteBatch* aSpriteBatch, wchar_t const* aText, BaseFontDesc aFontDesc);

    public:
        static std::shared_ptr<SpriteFont> CreateShared(wchar_t const* aFontFilePath, bool aForceSRGB = false);
        static std::unique_ptr<SpriteFont> CreateUnique(wchar_t const* aFontFilePath, bool aForceSRGB = false);

    };
}

#endif // !SOGE_SPRITE_FONT_HPP
