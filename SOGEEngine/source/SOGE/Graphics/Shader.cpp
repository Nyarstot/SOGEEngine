#include "sogepch.hpp"
#include "SOGE/Graphics/Shader.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    VertexShader::VertexShader(SOGE_SHADER_DESC aShaderDesc)
        : ShaderBase(aShaderDesc.name, aShaderDesc.path)
    {
        mShaderDesc = aShaderDesc;
    }

    VertexShader::~VertexShader()
    {

    }

    HRESULT VertexShader::Compile()
    {
        ID3DBlob* errorVertexCode = nullptr;
        ZeroMemory(&errorVertexCode, sizeof(errorVertexCode));

        HRESULT result = D3DCompileFromFile(
            mPath,
            nullptr,
            nullptr,
            mShaderDesc.entryPoint,
            mShaderDesc.target,
            D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
            0,
            &mVertexShaderByteCode,
            &errorVertexCode
        );

        if (FAILED(result)) {
            if (errorVertexCode) {
                char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());
                SOGE_ERROR_LOG("Compile shader error: {0}", compileErrors);
            }
            else {
                // TODO: set shader name to error logging
                SOGE_ERROR_LOG("Shader file doesn't exist or corrupted");
            }
        }

        return result;
    }

    HRESULT VertexShader::Create()
    {
        if (mVertexShaderByteCode == nullptr) {
            SOGE_ERROR_LOG("The vertex shader cannot be created because it has not yet been compiled.");
            return E_ACCESSDENIED;
        }

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreateVertexShader(
            mVertexShaderByteCode->GetBufferPointer(), mVertexShaderByteCode->GetBufferSize(),
            nullptr, &mVertexShader
        );

        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to create vertex shader");
        }

        const D3D11_INPUT_ELEMENT_DESC layout[] = {
            D3D11_INPUT_ELEMENT_DESC {
                "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0
            },
            D3D11_INPUT_ELEMENT_DESC {
                "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0
            }
        };

        result = device->CreateInputLayout(
            layout, 2u,
            mVertexShaderByteCode->GetBufferPointer(),
            mVertexShaderByteCode->GetBufferSize(),
            &mInputLayout
        );

        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to create input layout");
        }

        return result;
    }

    HRESULT VertexShader::CompileAndCreate()
    {
        HRESULT result = Compile();
        if (FAILED(result)) return result;

        result = Create();
        if (FAILED(result)) return result;

        return result;
    }

    void VertexShader::Bind()
    {
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();
        context->VSSetShader(mVertexShader.Get(), nullptr, 0u);
    }

    PixelShader::PixelShader(SOGE_SHADER_DESC aShaderDesc)
        : ShaderBase(aShaderDesc.name, aShaderDesc.path)
    {
        mShaderDesc = aShaderDesc;
    }

    PixelShader::~PixelShader()
    {

    }

    HRESULT PixelShader::Compile()
    {
        ID3DBlob* errorPixelCode = nullptr;
        HRESULT res = D3DCompileFromFile
        (
            mPath,
            nullptr, // macro
            nullptr,
            mShaderDesc.entryPoint,
            mShaderDesc.target,
            D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
            0,
            &mPixelShaderByteCode,
            &errorPixelCode
        );

        if (FAILED(res)) {
            if (errorPixelCode) {
                char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());
                SOGE_ERROR_LOG("Compile shader error: {0}", compileErrors);
            }
            else {
                // TODO: set shader name to error logging
                SOGE_ERROR_LOG("Shader file doesn't exist or corrupted");
            }
        }

        return res;
    }

    HRESULT PixelShader::Create()
    {
        if (mPixelShaderByteCode == nullptr) {
            SOGE_ERROR_LOG("The pixel shader cannot be created because it has not yet been compiled.");
            return E_ACCESSDENIED;
        }

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreatePixelShader(
            mPixelShaderByteCode->GetBufferPointer(), mPixelShaderByteCode->GetBufferSize(),
            nullptr, &mPixelShader
        );

        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to create pixel shader");
        }

        return result;
    }

    HRESULT PixelShader::CompileAndCreate()
    {
        HRESULT result = Compile();
        if (FAILED(result)) return result;

        result = Create();
        if (FAILED(result)) return result;

        return result;
    }

    void PixelShader::Bind()
    {
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();
        context->PSSetShader(mPixelShader.Get(), nullptr, 0u);
    }

}