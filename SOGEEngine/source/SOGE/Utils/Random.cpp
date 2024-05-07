#include "sogepch.hpp"
#include "SOGE/Utils/Random.hpp"


namespace soge
{
    RandomSeedDistributor* RandomSeedDistributor::sInstance = nullptr;
    RandomSeedDistributor* RandomSeedDistributor::GetInstance() {
        if (sInstance == nullptr) {
            sInstance = new RandomSeedDistributor();
        }

        return sInstance;
    }

    void RandomSeedDistributor::UpdateSeed(float aTotalTime)
    {
        float whole, fractional;
        fractional = std::modf(aTotalTime, &whole);
        std::string str = std::to_string(fractional);
        str = str.substr(2, str.size());
        this->mSeed = std::stoi(str);
    }

    void Random::UpdateRandomEngineSeeds(std::uint64_t aSeed)
    {
        mRandomEngine128 = XoshiroCpp::Xoroshiro128PlusPlus(aSeed);
        mRandomEngine256 = XoshiroCpp::Xoshiro256PlusPlus(aSeed);
    }

    Random::Random()
    {
        mSeedDist = RandomSeedDistributor::GetInstance();
        this->UpdateRandomEngineSeeds(mSeedDist->GetSeed());
    }

    Random::~Random()
    {

    }

    int Random::RandInt(unsigned int aLeftLim, unsigned int aRightLim)
    {
        this->UpdateRandomEngineSeeds(mSeedDist->GetSeed());
        std::uniform_int_distribution<int> dist(aLeftLim, aRightLim);
        return dist(mRandomEngine256);
    }

    double Random::RandDouble(unsigned int aLeftLim, unsigned int aRightLim)
    {
        this->UpdateRandomEngineSeeds(mSeedDist->GetSeed());
        double randI = (double)this->RandInt(aLeftLim, aRightLim);
        double randD = this->RandDoubleNorm();
        return randI + randD;
    }

    bool Random::RandBool()
    {
        this->UpdateRandomEngineSeeds(mSeedDist->GetSeed());
        return (bool)this->RandInt(0, 1);
    }

    double Random::RandDoubleNorm()
    {
        this->UpdateRandomEngineSeeds(mSeedDist->GetSeed());
        double a = XoshiroCpp::DoubleFromBits(mRandomEngine256());
        SOGE_INFO_LOG("value: {0}", a);
        SOGE_INFO_LOG("seed: {0}", mSeedDist->GetSeed());
        return a;
    }

    std::shared_ptr<Random> Random::CreateShared()
    {
        return std::make_shared<Random>();
    }

    std::unique_ptr<Random> Random::CreateUnique()
    {
        return std::make_unique<Random>();
    }

}