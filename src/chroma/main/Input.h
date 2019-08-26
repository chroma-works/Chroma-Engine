#pragma once

//from:https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Input.h (few adjustments are made)
namespace Chroma
{
    class Input
    {
    public:
        struct Pair
        {
            float x;
            float y;

            Pair(float a, float b)
                : x(a), y(b)
            {}
        };

        inline static bool IsKeyPressed(int keycode) { return s_instance->IsKeyPressedImpl(keycode); }

        inline static bool IsMouseButtonPressed(int button) { return s_instance->IsMouseButtonPressedImpl(button); }
        inline static Pair GetMousePosition() { return s_instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_instance->GetMousePositionImpl().x; }
        inline static float GetMouseY() { return s_instance->GetMousePositionImpl().y; }
    protected:

    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual Pair GetMousePositionImpl() = 0;
    private:
        static Input* s_instance;
    };
}