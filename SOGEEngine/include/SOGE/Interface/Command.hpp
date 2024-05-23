#ifndef SOGE_COMMAND_HPP
#define SOGE_COMMAND_HPP

namespace soge
{
    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void Execute() = 0;

    };
}

#endif // !SOGE_COMMAND_HPP
