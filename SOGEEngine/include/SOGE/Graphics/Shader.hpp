#ifndef SOGE_SHADER_HPP
#define SOGE_SHADER_HPP

#include "SOGE/Engine/EngineSetup.hpp"

#include <d3d11.h>
#include <d3dcompiler.h>

namespace soge
{
    class ShaderBase
    {
    protected:
        std::wstring mName;
        std::wstring mPath;

    public:
        ShaderBase(const std::wstring& aName, const std::wstring& aPath)
            : mName(aName), mPath(aPath)
        {

        }

        virtual ~ShaderBase() = default;
        virtual HRESULT Compile() = 0;
        virtual HRESULT Create() = 0;
        virtual HRESULT CompileAndCreate() = 0;
        virtual void Bind() = 0;

        std::wstring GetName() const { return mName; }
        std::wstring GetPath() const { return mPath; }

    };

    class VertexShader : public ShaderBase
    {
    private:
        wrl::ComPtr<ID3DBlob> mVertexShaderByteCode;
        wrl::ComPtr<ID3D11VertexShader> mVertexShader;
        wrl::ComPtr<ID3D11InputLayout> mInputLayout;

    public:
        VertexShader(const std::wstring& aName, const std::wstring& aPath);
        ~VertexShader();

        HRESULT Compile() override;
        virtual HRESULT Create() override;
        virtual HRESULT CompileAndCreate() override;
        virtual void Bind() override;

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

    public:
        PixelShader(const std::wstring& aName, const std::wstring& aPath);
        ~PixelShader();

        HRESULT Compile() override;
        virtual HRESULT Create() override;
        virtual HRESULT CompileAndCreate() override;
        virtual void Bind() override;

        ID3DBlob* GetCompiled() const { return mPixelShaderByteCode.Get(); }
        ID3D11PixelShader* GetShader() const { return mPixelShader.Get(); }
    };
}

#endif // !SOGE_SHADER_HPP
