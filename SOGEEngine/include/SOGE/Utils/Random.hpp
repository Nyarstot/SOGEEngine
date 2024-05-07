#ifndef SOGE_RANDOM_HPP
#define SOGE_RANDOM_HPP

#include <XoshiroCpp/XoshiroCpp.hpp>

namespace soge
{
    class RandomSeedDistributor
    {
    private:
        std::uint64_t mSeed;
        float mTotalTime;

    protected:
        RandomSeedDistributor() {
            std::stringstream ss;
            ss << std::this_thread::get_id();
            mSeed = std::stoull(ss.str());
            mTotalTime = 0.0f;
        }
        static RandomSeedDistributor* sInstance;

    public:
        RandomSeedDistributor(RandomSeedDistributor&) = delete;
        void operator= (RandomSeedDistributor&) = delete;

        void UpdateSeed(float aTotalTime);
        const std::uint64_t const GetSeed() { return mSeed; }

    public:
        static RandomSeedDistributor* GetInstance();

    };

    class Random
    {
    private:
        RandomSeedDistributor* mSeedDist = nullptr;
        XoshiroCpp::Xoroshiro128PlusPlus mRandomEngine128;
        XoshiroCpp::Xoshiro256PlusPlus mRandomEngine256;

    protected:
        void UpdateRandomEngineSeeds(std::uint64_t aSeed);

    public:
        Random();
        ~Random();

        int RandInt(unsigned int aLeftLim, unsigned int aRightLim);
        double RandDouble(unsigned int aLeftLim, unsigned int aRightLim);
        bool RandBool();
        double RandDoubleNorm();

    public:
        static std::shared_ptr<Random> CreateShared();
        static std::unique_ptr<Random> CreateUnique();

    };

    class ShuffleBag
    {
    private:


    public:


    };
}

#endif // !SOGE_RANDOM_HPP
