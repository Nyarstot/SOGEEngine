#include "sogepch.hpp"
#include "SOGE/Graphics/DebugSystem/GraphicsException.hpp"

#include "SOGE/Graphics/DebugSystem/dxerr.hpp"

namespace soge
{
    HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
        : GraphicsException(line, file), result(hr)
    {
        // join all info messages with newlines into single string
        for (const auto& m : infoMsgs)
        {
            mInfo += m;
            mInfo.push_back('\n');
        }
        // remove final newline if exists
        if (!mInfo.empty())
        {
            mInfo.pop_back();
        }
    }

    const char* HrException::GetType() const noexcept
    {
        return "Engine Graphics Exception";
    }

    HRESULT HrException::GetErrorCode() const noexcept
    {
        return result;
    }

    std::string HrException::GetErrorString() const noexcept
    {
        return (const char*)DXGetErrorString(result);
    }

    std::string HrException::GetErrorDescription() const noexcept
    {
        WCHAR buf[512];
        DXGetErrorDescriptionW(result, buf, sizeof(buf));
        return (const char*)buf;
    }

    std::string HrException::GetErrorInfo() const noexcept
    {
        return mInfo;
    }

    const char* HrException::what() const noexcept
    {
        std::ostringstream oss;
        oss << GetType() << std::endl
            << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
            << std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
            << "[Error String] " << GetErrorString() << std::endl
            << "[Description] " << GetErrorDescription() << std::endl;

        if (!mInfo.empty())
        {
            oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
        }

        oss << GetOriginString();
        mWhatBuffer = oss.str();
        return mWhatBuffer.c_str();
    }


    InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
        : GraphicsException(line, file)
    {
        // join all info messages with newlines into single string
        for (const auto& m : infoMsgs)
        {
            mInfo += m;
            mInfo.push_back('\n');
        }

        // remove final newline if exists
        if (!mInfo.empty())
        {
            mInfo.pop_back();
        }
    }

    const char* InfoException::GetType() const noexcept
    {
        return "Engine Graphics Info Exception";
    }

    std::string InfoException::GetErrorInfo() const noexcept
    {
        return mInfo;
    }

    const char* InfoException::what() const noexcept
    {
        std::ostringstream oss;
        oss << GetType() << std::endl
            << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
        oss << GetOriginString();

        mWhatBuffer = oss.str();
        return mWhatBuffer.c_str();
    }


    const char* DeviceRemovedException::GetType() const noexcept
    {
        return "Engine Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
    }


}