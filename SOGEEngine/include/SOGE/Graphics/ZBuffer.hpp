#ifndef SOGE_DEPTH_STENCIL_VIEW_HPP
#define SOGE_DEPTH_STENCIL_VIEW_HPP

#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Containers/Simple.hpp"
#include <d3d11.h>

namespace soge
{
    class ZBuffer
    {
    private:
        wrl::ComPtr<ID3D11DepthStencilState> mDepthStencilState;
        wrl::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
        wrl::ComPtr<ID3D11Texture2D> mStencilBuffer;
        Point2D mStencilSize;

    public:
        ZBuffer(const Point2D& aSize);
        ~ZBuffer();

        ID3D11Texture2D* GetStencilBuffer() const { return mStencilBuffer.Get(); }
        ID3D11Texture2D* const* GetStencilBufferAddress() { return mStencilBuffer.GetAddressOf(); }
        ID3D11DepthStencilView* GetDepthStencilView() const { return mDepthStencilView.Get(); }
        ID3D11DepthStencilView* const* GetDepthStencilViewAddress() { return mDepthStencilView.GetAddressOf(); }
        Point2D& const GetStencilBufferSize() { return mStencilSize; }

    public:
        static std::shared_ptr<ZBuffer> CreateShared(const Point2D& aSize);
        static std::unique_ptr<ZBuffer> CreateUnique(const Point2D& aSize);

    };
}

#endif // !SOGE_DEPTH_STENCIL_VIEW_HPP
