#ifndef SOGE_COLOR_HPP
#define SOGE_COLOR_HPP

namespace soge
{
    class ColorRGBA8
    {
    private:
        std::uint8_t mR;
        std::uint8_t mG;
        std::uint8_t mB;
        std::uint8_t mA;

    public:
        ColorRGBA8();
        ~ColorRGBA8();

    };
}

#endif // !SOGE_COLOR_HPP
