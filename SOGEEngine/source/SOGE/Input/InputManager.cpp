#include "sogepch.hpp"
#include "SOGE/Input/InputManager.hpp"

namespace soge
{
    InputManager* InputManager::sInstance = nullptr;
    InputManager* InputManager::GetInstance() {
        if (sInstance == nullptr) {
            sInstance = new InputManager();
        }

        return sInstance;
    }

    InputManager::InputManager()
        //: mEventFunc(fnEventCallback(NULL))
    {
    }

    void InputManager::Init(const std::unique_ptr<Window>& aSystemWindow)
    {
        mKeyboardDevice = std::make_unique<DirectX::Keyboard>();
        mMouseDevice = std::make_unique<DirectX::Mouse>();
        //mGamepadDevice = std::make_unique<DirectX::GamePad>();

        mEventFunc = aSystemWindow->mEventCallbackFunction;
        mMouseDevice->SetWindow((HWND)aSystemWindow->GetHandle());
    }

    LONG_PTR InputManager::HandleInput(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
    {
        switch (umessage)
        {
        case WM_ACTIVATE:
        case WM_ACTIVATEAPP:
        case WM_INPUT:
            DirectX::Keyboard::ProcessMessage(umessage, wparam, lparam);
            break;

        case WM_KEYDOWN:
        {
            if (mLastPressedKeyCode == wparam) {
                mKeyRepeatCounter++;
            }
            else {
                mKeyRepeatCounter = 1;
            }

            DirectX::Keyboard::ProcessMessage(umessage, wparam, lparam);
            KeyPressedEvent fnEvent(wparam, mKeyRepeatCounter);
            mEventFunc(fnEvent);

            mLastPressedKeyCode = wparam;
            break;
        }
        case WM_SYSKEYDOWN:
        {
            if (wparam == VK_RETURN && (lparam & 0x60000000) == 0x20000000)
            {
                // This is where you'd implement the classic ALT+ENTER hotkey for fullscreen toggle
            }
            DirectX::Keyboard::ProcessMessage(umessage, wparam, lparam);
            break;
        }


        case WM_SYSKEYUP:
        case WM_KEYUP:
        {
            KeyReleasedEvent fnEvent(wparam);
            mEventFunc(fnEvent);
            DirectX::Keyboard::ProcessMessage(umessage, wparam, lparam);
            break;
        }
        default:
        {
            //mCurrentKeyCode = -1;
            return DefWindowProcW(hwnd, umessage, wparam, lparam);
        }
        }
    }

    bool InputManager::IsKeyPressed(Keys aKey)
    {
        //return mPressedKeysSet.count(aKey) != 0;
        //return mKeyboardTracker.IsKeyPressed(DirectX::Keyboard::A);
        auto keyboardState = mKeyboardDevice->GetState();
        return keyboardState.IsKeyDown((DirectX::Keyboard::Keys)aKey);
    }

    bool InputManager::IsKeyReleased(Keys aKey)
    {
        auto keyboardState = mKeyboardDevice->GetState();
        return keyboardState.IsKeyUp((DirectX::Keyboard::Keys)aKey);
    }

    bool InputManager::IsMouseButtonPressed(int aMButtonCode)
    {
        return false;
    }

    float InputManager::GetMouseX() const
    {
        return 0.0f;
    }

    float InputManager::GetMouseY() const
    {
        return 0.0f;
    }

}