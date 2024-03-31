#ifndef SOGE_INPUT_MANGER_HPP
#define SOGE_INPUT_MANGER_HPP

#include "SOGE/System/Window.hpp"
#include "SOGE/Input/Keys.hpp"

#include "SOGE/Event/Event.hpp"
#include "SOGE/Event/InputEvents/KeyboardEvents.hpp"

namespace soge
{
    class InputManager
    {
        using fnEventCallback = std::function<void(Event&)>;

    private:
        //fnEventCallback& mEventFunc;
        fnEventCallback mEventFunc;
        std::unordered_set<Keys> mPressedKeysSet;

    protected:
        InputManager();
        static InputManager* sInstance;

        void AddPressedKey(int aKeyCode);
        void RemovePressedKey(int aKeyCode);

    public:
        InputManager(InputManager&)             = delete;
        void operator = (const InputManager&)   = delete;

        void Init(const std::unique_ptr<Window>& aSystemWindow);
        LONG_PTR HandleInput(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
        bool IsKeyPressed(Keys aKey);
        bool IsMouseButtonPressed(int aMButtonCode);

        float GetMouseX() const;
        float GetMouseY() const;

    public:
        static InputManager* GetInstance();

    };
}

#endif // !SOGE_INPUT_MANGER_HPP
