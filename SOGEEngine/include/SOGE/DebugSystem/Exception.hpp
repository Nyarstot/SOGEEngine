#ifndef SOGE_EXCEPTION_HPP
#define SOGE_EXCEPTION_HPP

#include <exception>

namespace soge
{
    class DXException : public std::exception
    {
    private:
        HRESULT mResult;

    public:
        DXException(HRESULT aResult) : mResult(aResult) {}
        ~DXException() = default;

        const char* what() const noexcept override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X",
                static_cast<unsigned int>(mResult));
            return s_str;
        }

    };

    // Must to be inline

    inline void DXThrowIfFailed(HRESULT aResult) {
        if (FAILED(aResult)) {
            auto& exception = DXException(aResult);
            SOGE_ERROR_LOG("{0}", exception.what());
            throw exception;
        }
        return;
    }

    inline void DXThrowIfFailed(HRESULT aResult, const char* aMessage) {
        if (FAILED(aResult)) {
            auto& exception = DXException(aResult);
            SOGE_ERROR_LOG("HRESULT: {0} \n MESSAGE: {1}", exception.what(), aMessage);
            throw exception;
        }
        return;
    }
}

#endif // !SOGE_EXCEPTION_HPP
