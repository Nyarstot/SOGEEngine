#ifndef SOGE_AI_HPP
#define SOGE_AI_HPP

#include <SOGE/Interface/AIInterfaces.hpp>

namespace soge
{
    class AI : public IAIBase
    {
    private:


    public:
        AI();
        ~AI();

        void Update(float aDeltaTime) override;
        void Reset() override;

    };
}

#endif // !SOGE_AI_HPP
