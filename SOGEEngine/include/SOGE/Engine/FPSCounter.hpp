#ifndef SOGE_FPS_COUNTER_HPP
#define SOGE_FPS_COUNTER_HPP

namespace soge
{
    class FPSCounter
    {
    private:
        std::chrono::time_point<std::chrono::steady_clock> mPrevTime;
        float mTotalTime            = 0;
        float mFrameTime            = 0;
        float mDeltaTime            = 0;
        float mFPS                  = 0;
        unsigned int mFrameCount    = 0;

    protected:
        void Init();

    public:
        FPSCounter();
        ~FPSCounter();

        void AddFrame();
        float GetDeltaTime();
        float GetFrameTime();
        float GetFPS(bool aRound=true);

    public:
        static std::unique_ptr<FPSCounter> Create();

    };
}

#endif // !SOGE_FPS_COUNTER_HPP
