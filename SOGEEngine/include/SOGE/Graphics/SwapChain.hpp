#ifndef SOGE_SWAP_CHAIN_HPP
#define SOGE_SWAP_CHAIN_HPP

#include <d3d.h>
#include <d3d11.h>

#include <SOGE/Engine/EngineSetup.hpp>
#include <SOGE/System/Window.hpp>

namespace soge
{
    class SwapChain
    {
    private:
        wrl::ComPtr<IDXGISwapChain> mSwapChain;
        wrl::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

    protected:
        HRESULT Init(const std::unique_ptr<Window>& aSystemWindow);

    public:
        SwapChain() = default;
        SwapChain(const std::unique_ptr<Window>& aSystemWindow);
        ~SwapChain();

        HRESULT Present(bool aVSync);
        void Release();

        ID3D11RenderTargetView* GetRenderTargetView() const { return mRenderTargetView.Get(); }
        ID3D11RenderTargetView* const* GetAddresOfRenderTargetView() { return mRenderTargetView.GetAddressOf(); }

    public:
        static std::unique_ptr<SwapChain> Create(const std::unique_ptr<Window>& aSystemWindow);

    };
}

#endif // !SOGE_SWAP_CHAIN_HPP
