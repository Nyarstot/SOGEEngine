#include "sogepch.hpp"
#include "SOGE/Utils/Random.hpp"


namespace soge
{
    void Random::UpdateRandomEngineSeeds(std::uint64_t aSeed)
    {
        mRandomEngine128 = XoshiroCpp::Xoroshiro128PlusPlus(aSeed);
        mRandomEngine256 = XoshiroCpp::Xoshiro256PlusPlus(aSeed);
    }

    Random::Random(std::uint64_t aSeed)
    {
        this->SetSeed(aSeed);
        this->UpdateRandomEngineSeeds(mSeed);
    }

    Random::~Random()
    {

    }

    int Random::RandInt(unsigned int aLeftLim, unsigned int aRightLim)
    {
        std::uniform_int_distribution<int> dist(aLeftLim, aRightLim);
        return dist(mRandomEngine256);
    }

    double Random::RandDouble(unsigned int aLeftLim, unsigned int aRightLim)
    {
        double randI = (double)this->RandInt(aLeftLim, aRightLim);
        double randD = this->RandDoubleNorm();
        return randI + randD;
    }

    bool Random::RandBool()
    {
        return (bool)this->RandInt(0, 1);
    }

    double Random::RandDoubleNorm()
    {
        return XoshiroCpp::DoubleFromBits(mRandomEngine256());
    }

    double Random::RandDoubleNorm(int aAfterDecimalCount)
    {
        return std::floor(aAfterDecimalCount * this->RandDoubleNorm());
    }

    std::shared_ptr<Random> Random::CreateShared(std::uint64_t aSeed)
    {
        return std::make_shared<Random>(aSeed);
    }

    std::unique_ptr<Random> Random::CreateUnique(std::uint64_t aSeed)
    {
        return std::make_unique<Random>(aSeed);
    }


}