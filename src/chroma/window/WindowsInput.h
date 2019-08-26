#pragma once

#include "Chroma/main/Input.h"

//from:https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Platform/Windows/WindowsInput.h (few adjustments are made)

namespace Chroma {

    class WindowsInput : public Chroma::Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual Pair GetMousePositionImpl() override;
    };

}