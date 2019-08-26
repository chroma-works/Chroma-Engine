#include <GLFW/glfw3.h>
#include <chroma/main/Application.h>
#include "WindowsInput.h"
#include <chroma/main/Log.h>

//from:https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Platform/Windows/WindowsInput.cpp (few adjustments are made)

namespace Chroma {

    Input* Input::s_instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        auto window = Application::Get().GetWindow()->GetWindowHandle();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = Application::Get().GetWindow()->GetWindowHandle();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    Input::Pair WindowsInput::GetMousePositionImpl()
    {
        auto window = Application::Get().GetWindow()->GetWindowHandle();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return Pair((float)xpos, (float)ypos);
    }
}