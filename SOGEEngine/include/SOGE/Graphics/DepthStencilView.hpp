#ifndef SOGE_DEPTH_STENCIL_VIEW_HPP
#define SOGE_DEPTH_STENCIL_VIEW_HPP

#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Containers/Simple.hpp"
#include <d3d11.h>

namespace soge
{
    class DepthStencilView
    {
    private:
        wrl::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
        wrl::ComPtr<ID3D11Texture2D> mStencilBuffer;
        Point2D mStencilSize;

    public:
        DepthStencilView(const Point2D& aSize);
        ~DepthStencilView();

        ID3D11Texture2D* GetStencilBuffer() const { return mStencilBuffer.Get(); }
        ID3D11Texture2D* const* GetStencilBufferAddress() { return mStencilBuffer.GetAddressOf(); }
        ID3D11DepthStencilView* GetDepthStencilView() const { return mDepthStencilView.Get(); }
        ID3D11DepthStencilView* const* GetDepthStencilViewAddress() { return mDepthStencilView.GetAddressOf(); }
        Point2D& const GetStencilBufferSize() { return mStencilSize; }

    public:
        static std::shared_ptr<DepthStencilView> CreateShared(const Point2D& aSize);
        static std::unique_ptr<DepthStencilView> CreateUnique(const Point2D& aSize);

    };
}

#endif // !SOGE_DEPTH_STENCIL_VIEW_HPP
