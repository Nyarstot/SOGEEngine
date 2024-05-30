#ifndef SOGE_SHADER_HPP
#define SOGE_SHADER_HPP

#include "SOGE/Interface/GraphicsInterfaces.hpp"
#include "SOGE/Engine/EngineSetup.hpp"

#include <d3d11.h>
#include <d3dcompiler.h>

namespace soge
{
    typedef struct SOGE_SHADER_DESC
    {
        LPCWSTR name;
        LPCWSTR path;
        LPCSTR entryPoint;
        LPCSTR target;
    };

    enum ShaderTypes
    {
        SOGE_VERTEX_SHADER  = 0x00,
        SOGE_PIXEL_SHADER   = 0x01
    };

    class ShaderBase : public IBindable
    {
    protected:
        LPCWSTR mName;
        LPCWSTR mPath;

    public:
        ShaderBase(const LPCWSTR& aName, const LPCWSTR& aPath)
            : mName(aName), mPath(aPath)
        {

        }

        virtual ~ShaderBase() = default;
        virtual HRESULT Compile() = 0;
        virtual HRESULT Create() = 0;
        virtual HRESULT CompileAndCreate() = 0;
        virtual void Bind() noexcept = 0;

        LPCWSTR GetName() const { return mName; }
        LPCWSTR GetPath() const { return mPath; }

    };

    class VertexShader : public ShaderBase
    {
    private:
        wrl::ComPtr<ID3DBlob> mVertexShaderByteCode;
        wrl::ComPtr<ID3D11VertexShader> mVertexShader;
        wrl::ComPtr<ID3D11InputLayout> mInputLayout;
        SOGE_SHADER_DESC mShaderDesc;

    public:
        VertexShader(SOGE_SHADER_DESC aShaderDesc);
        ~VertexShader();

        HRESULT Compile() override;
        virtual HRESULT Create() override;
        virtual HRESULT CompileAndCreate() override;
        void Bind() noexcept override;

        ID3DBlob* GetCompiled() const { return mVertexShaderByteCode.Get(); }
        ID3D11VertexShader* GetShader() const { return mVertexShader.Get(); }
        ID3D11InputLayout* GetInputLayout() const { return mInputLayout.Get(); }
        ID3D11InputLayout* const* GetAddresOfInputLayout() { return mInputLayout.GetAddressOf(); }
    };

    class PixelShader : public ShaderBase
    {
    private:
        wrl::ComPtr<ID3DBlob> mPixelShaderByteCode;
        wrl::ComPtr<ID3D11PixelShader> mPixelShader;
        SOGE_SHADER_DESC mShaderDesc;

    public:
        PixelShader(SOGE_SHADER_DESC aShaderDesc);
        ~PixelShader();

        HRESULT Compile() override;
        virtual HRESULT Create() override;
        virtual HRESULT CompileAndCreate() override;
        void Bind() noexcept override;

        ID3DBlob* GetCompiled() const { return mPixelShaderByteCode.Get(); }
        ID3D11PixelShader* GetShader() const { return mPixelShader.Get(); }
    };
}

#endif // !SOGE_SHADER_HPP
