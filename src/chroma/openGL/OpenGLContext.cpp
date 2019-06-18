
#include <thirdparty/glad/include/glad/glad.h>

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "OpenGLContext.h"
#include <chroma/main/Log.h>


namespace Chroma
{
    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : m_window_handle(window)
    {
        if (!window)
        {
            CH_ERROR("Failed to create GLFW window");
            glfwTerminate();
        }
    }

    void OpenGLContext::Init()
    {
        CH_INFO("Chroma-Engine v.0");
        glfwMakeContextCurrent(m_window_handle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (status == 0)
            CH_ERROR("Failed to initialize Glad");

        std::string opengl_info = std::string();
        opengl_info += std::string("OpenGL Info:\n") + std::string("\tVendor: ") + std::string((char*)glGetString(GL_VENDOR)) + "\n"
            + std::string("\tRenderer: ") + std::string((char*)glGetString(GL_RENDERER)) + "\n" + std::string("\tVersion: ")
            + std::string((char*)glGetString(GL_VERSION));

        CH_INFO(opengl_info);

    }

    void OpenGLContext::SwapBuffers()
    {
        glClearColor(0.184f, 0.062f, 0.129f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window_handle);
    }
}