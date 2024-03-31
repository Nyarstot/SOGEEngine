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

    void InputManager::AddPressedKey(int aKeyCode)
    {
        mPressedKeysSet.insert(Keys(aKeyCode));
    }

    void InputManager::RemovePressedKey(int aKeyCode)
    {
        mPressedKeysSet.erase(Keys(aKeyCode));
    }

    void InputManager::Init(const std::unique_ptr<Window>& aSystemWindow)
    {
        mEventFunc = aSystemWindow->mEventCallbackFunction;
    }

    LONG_PTR InputManager::HandleInput(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
    {
        switch (umessage)
        {
        case WM_KEYDOWN:
        {
            //mCurrentKeyCode = wparam;
            KeyPressedEvent fnEvent(wparam, 1);
            mEventFunc(fnEvent);
            AddPressedKey(wparam);
            break;
        }
        case WM_KEYUP:
        {
            //mCurrentKeyCode = wparam;
            KeyReleasedEvent fnEvent(wparam);
            mEventFunc(fnEvent);
            RemovePressedKey(wparam);
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
        return mPressedKeysSet.count(aKey) != 0;
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