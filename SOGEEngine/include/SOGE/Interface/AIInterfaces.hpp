#ifndef SOGE_AI_INTERFACES_HPP
#define SOGE_AI_INTERFACES_HPP

namespace soge
{
    class IAIBase
    {
    public:
        virtual ~IAIBase() = default;

        virtual void Reset() = 0;
        virtual void Update(float aDeltaTime) = 0;

    };
}

#endif // !SOGE_AI_INTERFACES_HPP
