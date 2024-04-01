#ifndef SOGE_FSA_HPP
#define SOGE_FSA_HPP

namespace soge
{
    class FixedSizeAllocator final
    {
        const std::uint32_t DEFAULT_SIZE = 4096;

        struct MemoryPage
        {
            MemoryPage* next;
            int numInt;
            int fh;
        };

        struct MemoryBlock
        {
            int freeIndex;
        };

    private:
        MemoryPage* mMemPage;
        std::uint32_t mBlockSize;

    private:
        MemoryPage* CreateMemoryPage() const;

    public:
        FixedSizeAllocator();
        ~FixedSizeAllocator();

        void Init(std::uint32_t aBlockSize);
        void* Alloc(std::uint32_t aBlockSize);

        void Destroy();
        void Free(void* aMemBlock);

        bool IsContainAddress(void* aAddressPtr);

    };
}

#endif // !SOGE_FSA_HPP
