#ifndef SOGE_WINDOW_HPP
#define SOGE_WINDOW_HPP

#include "SOGE/Event/Event.hpp"
#include <Windows.h>

namespace soge
{
    struct WindowDesc
    {
        std::uint32_t height;
        std::uint32_t width;
        LPCWSTR title;

        WindowDesc(
            std::uint32_t aWidth = 720,
            std::uint32_t aHeight = 1270,
            LPCWSTR aTitle = L"SOGEEngine"
        )
            : height(aHeight), width(aWidth), title(aTitle)
        {

        }
    };

    class Window
    {
        friend class InputManager;
        using fnEventCallback = std::function<void(Event&)>;
        using fnEventCallbackPtr = fnEventCallback*;

    private:
        MSG mWindowMessage  = {};
        HINSTANCE mHInstance = nullptr;
        HWND mWindowHandle = nullptr;
        WindowDesc mWindowDescriptor;
        fnEventCallback mEventCallbackFunction;

    private:
        void Init(const WindowDesc& aWindowDesc);
        void Shutdown();

    public:
        Window(const WindowDesc& aWindowDesc);
        ~Window();

        void Show();
        void OnUpdate();
        void SetEventCallback(const fnEventCallback& aCallbackFunction);

        virtual void* GetHandle() const { return mWindowHandle; }
        std::uint32_t GetHeight() const { return mWindowDescriptor.height; }
        std::uint32_t GetWidth() const { return mWindowDescriptor.width; }
        LPCWSTR GetTitle() const { return mWindowDescriptor.title; }

    public:
        static std::unique_ptr<Window> Create(const WindowDesc& aWindowDesc = WindowDesc());

    };
}

#endif // !SOGE_WINDOW_HPP
