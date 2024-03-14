#ifndef SOGE_DXGI_INFO_MANAGER_HPP
#define SOGE_DXGI_INFO_MANAGER_HPP

#include "SOGE/Engine/EngineSetup.hpp"

#include <sdkddkver.h>
#include <dxgidebug.h>

namespace soge
{
    class DXGIInfoManager
    {
    private:
        unsigned long long next = 0u;
        wrl::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;

    protected:
        DXGIInfoManager();
        static DXGIInfoManager* sInstance;

    public:
        DXGIInfoManager(DXGIInfoManager&) = delete;
        void operator = (DXGIInfoManager&) = delete;

        DXGIInfoManager(const DXGIInfoManager&)             = delete;
        DXGIInfoManager& operator=(const DXGIInfoManager&)  = delete;

        void Set() noexcept;
        std::vector<std::string> GetMessages() const;

    public:
        static DXGIInfoManager* GetInstance();

    };
}

#endif // !SOGE_DXGI_INFO_MANAGER_HPP
