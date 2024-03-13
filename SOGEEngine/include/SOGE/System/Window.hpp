#ifndef SOGE_WINDOW_HPP
#define SOGE_WINDOW_HPP

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
    private:


    private:
        MSG mWindowMessage  = {};
        HINSTANCE mHInstance = nullptr;
        HWND mWindowHandle = nullptr;
        WindowDesc mWindowDescriptor;

    private:
        void Init(const WindowDesc& aWindowDesc);
        void Shutdown();

    public:
        Window(const WindowDesc& aWindowDesc);
        ~Window();

        void Show();
        void OnUpdate();

        virtual void* GetHandle() const { return mWindowHandle; }
        std::uint32_t GetHeight() const { return mWindowDescriptor.height; }
        std::uint32_t GetWidth() const { return mWindowDescriptor.width; }
        LPCWSTR GetTitle() const { return mWindowDescriptor.title; }

    public:
        static std::unique_ptr<Window> Create(const WindowDesc& aWindowDesc = WindowDesc());

    };
}

#endif // !SOGE_WINDOW_HPP
