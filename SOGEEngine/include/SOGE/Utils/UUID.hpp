#ifndef SOGE_UUID_HPP
#define SOGE_UUID_HPP

#include <random>
#include <uuid_v4/uuid_v4.hpp>

namespace soge
{
    class UUIDGenerator
    {
    private:
        static UUIDv4::UUIDGenerator<std::mt19937> mUUIDGenerator;

    public:
        static UUIDv4::UUID GenerateUUID();

    };
}

#endif // !SOGE_UUID_HPP
