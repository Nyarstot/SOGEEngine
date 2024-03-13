#include "sogepch.hpp"
#include "SOGE/System/Window.hpp"
#include "SOGE/Engine/EngineAssert.hpp"

namespace soge
{
    std::unique_ptr<Window> Window::Create(const WindowDesc& aWindowDescriptor)
    {
        return std::make_unique<Window>(aWindowDescriptor);
    }

    //Input* gInputManager = Input::GetInstance();
    LRESULT CALLBACK WindowsWindowProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
    {
        //return gInputManager->HandleInput(hwnd, umessage, wparam, lparam);
        return DefWindowProcW(hwnd, umessage, wparam, lparam);
    }

    void Window::Init(const WindowDesc& aWindowDesc)
    {

        //////////////////////////
        // Setup descriptor data
        /////////////////////////

        mWindowDescriptor.height = aWindowDesc.height;
        mWindowDescriptor.width = aWindowDesc.width;
        mWindowDescriptor.title = aWindowDesc.title;

        /////////////////////////
        // Init windows window
        /////////////////////////

        mHInstance = GetModuleHandle(nullptr);

        WNDCLASSEX wc;

        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = WindowsWindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = mHInstance;
        wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
        wc.hIconSm = wc.hIcon;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = mWindowDescriptor.title;
        wc.cbSize = sizeof(WNDCLASSEX);

        // Register window class
        HRESULT result = RegisterClassEx(&wc);
        if (FAILED(result)) {
            SOGE_ERROR_LOG("Could not register window class");
        }

        RECT windowRect =
        {
            0,
            0,
            static_cast<LONG>(mWindowDescriptor.width),
            static_cast<LONG>(mWindowDescriptor.height)
        };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

        auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;
        int posX = (GetSystemMetrics(SM_CXSCREEN) - mWindowDescriptor.width) / 2;
        int posY = (GetSystemMetrics(SM_CYSCREEN) - mWindowDescriptor.height) / 2;

        mWindowHandle = CreateWindowEx
        (
            WS_EX_APPWINDOW,
            mWindowDescriptor.title,
            mWindowDescriptor.title,
            dwStyle,
            posX, posY,
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top,
            nullptr, nullptr, mHInstance, nullptr
        );

        if (this->mWindowHandle == NULL) {
            SOGE_ERROR_LOG("Failed to create windows window handler");
        }
    }

    void Window::Shutdown()
    {
        DestroyWindow(this->mWindowHandle);
    }

    Window::Window(const WindowDesc& aWindowDesc)
    {
        this->Init(aWindowDesc);
    }

    Window::~Window()
    {
        this->Shutdown();
    }

    void Window::Show()
    {
        ShowWindow(mWindowHandle, SW_SHOW);
        SetForegroundWindow(mWindowHandle);
        SetFocus(mWindowHandle);
        ShowCursor(true);
    }

    void Window::OnUpdate()
    {
        while (PeekMessage(&mWindowMessage, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&mWindowMessage);
            DispatchMessage(&mWindowMessage);

            //if (message.message == WM_KEYDOWN) {
            //    KeyPressedEvent fnEvent(message.wParam, 1);
            //    mEventCallbackFunction(fnEvent);
            //}
            //if (message.message == WM_KEYUP) {
            //    KeyReleasedEvent fnEvent(message.wParam);
            //    mEventCallbackFunction(fnEvent);
            //}
        }
    }

}