#ifndef SOGE_GRAPHICS_EXCEPTION_HPP
#define SOGE_GRAPHICS_EXCEPTION_HPP

#include "SOGE/DebugSystem/Exception.hpp"

namespace soge
{
    class GraphicsException : public Exception
    {
        using Exception::Exception;
    };

    class HrException : public GraphicsException
    {
    private:
        HRESULT result;
        std::string mInfo;

    public:
        HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;

        const char* GetType() const noexcept override;
        HRESULT GetErrorCode() const noexcept;
        std::string GetErrorString() const noexcept;
        std::string GetErrorDescription() const noexcept;
        std::string GetErrorInfo() const noexcept;

        const char* what() const noexcept override;

    };

    class InfoException : public GraphicsException
    {
    private:
        std::string mInfo;

    public:
        InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;

        const char* GetType() const noexcept override;
        std::string GetErrorInfo() const noexcept;

        const char* what() const noexcept override;
    };

    class DeviceRemovedException : public HrException
    {
        using HrException::HrException;

    private:
        std::string mReason;

    public:
        const char* GetType() const noexcept override;

    };
}

#endif // !SOGE_GRAPHICS_EXCEPTION_HPP
