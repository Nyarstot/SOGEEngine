#ifndef SOGE_RANDOM_HPP
#define SOGE_RANDOM_HPP

#include <XoshiroCpp/XoshiroCpp.hpp>

namespace soge
{
    class Random
    {
    private:
        std::uint64_t mSeed = 12345;
        XoshiroCpp::Xoroshiro128PlusPlus mRandomEngine128;
        XoshiroCpp::Xoshiro256PlusPlus mRandomEngine256;

    protected:
        void UpdateRandomEngineSeeds(std::uint64_t aSeed);

    public:
        Random(std::uint64_t aSeed = 12345);
        ~Random();

        int RandInt(unsigned int aLeftLim, unsigned int aRightLim);
        double RandDouble(unsigned int aLeftLim, unsigned int aRightLim);
        bool RandBool();

        double RandDoubleNorm();
        double RandDoubleNorm(int aAfterDecimalCount);

        void SetSeed(std::uint64_t aSeed) { mSeed = aSeed; this->UpdateRandomEngineSeeds(aSeed); }
        const std::uint64_t GetSeed() const { return mSeed; }

    public:
        static std::shared_ptr<Random> CreateShared(std::uint64_t aSeed = 12345);
        static std::unique_ptr<Random> CreateUnique(std::uint64_t aSeed = 12345);

    };

    class ShuffleBag
    {
    private:


    public:


    };
}

#endif // !SOGE_RANDOM_HPP
