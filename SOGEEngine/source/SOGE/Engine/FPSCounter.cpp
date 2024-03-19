#include "sogepch.hpp"
#include "SOGE/Engine/FPSCounter.hpp"

namespace soge
{
    void FPSCounter::Init()
    {
        mPrevTime = std::chrono::steady_clock::now();
    }

    FPSCounter::FPSCounter()
    {
        this->Init();
    }

    FPSCounter::~FPSCounter()
    {

    }

    void FPSCounter::AddFrame()
    {
        auto curTime    = std::chrono::steady_clock::now();
        mDeltaTime      = std::chrono::duration_cast<std::chrono::microseconds>(curTime - mPrevTime).count() / 1000000.0f;
        mPrevTime       = curTime;

        mTotalTime += mDeltaTime;
        mFrameCount++;

        if (mTotalTime > 1.0f) {
            float fps = mFrameCount / mTotalTime;

            mTotalTime -= 1.0f;
            mFrameCount = 0;
            mFPS        = fps;
        }
    }

    float FPSCounter::GetDeltaTime()
    {
        return mDeltaTime;
    }

    float FPSCounter::GetFPS()
    {
        return mFPS;
    }

    std::unique_ptr<FPSCounter> FPSCounter::Create()
    {
        return std::make_unique<FPSCounter>();
    }
}
