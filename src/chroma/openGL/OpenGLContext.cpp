
#include <thirdparty/glad/include/glad/glad.h>

#include <stdio.h>
#include <iostream>
#include "OpenGLContext.h"


namespace Chroma
{
    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : m_window_handle(window)
    {
        if (!window)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
    }

    void OpenGLContext::Init()
    {
        std::cout << "Chroma-Engine v. 0" << std::endl;
        glfwMakeContextCurrent(m_window_handle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(status == 0)
            std::cout << "Failed to initialize Glad!" << std::endl;

        std::cout << "OpenGL Info:" << std::endl;
        std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_window_handle);
        //glClearColor(0.184f, 0.062f, 0.129f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}