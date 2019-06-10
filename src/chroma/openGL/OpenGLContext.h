#pragma once

#include <chroma/renderer/RenderContext.h>
#include <GLFW/glfw3.h>

namespace Chroma
{
    class OpenGLContext : public RenderContext
    {
    public:
        OpenGLContext(GLFWwindow* window);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_window_handle;

    };
}
