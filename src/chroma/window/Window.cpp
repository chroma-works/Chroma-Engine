#include "Window.h"
#include <chroma/main/Log.h>
#include <chroma/openGL/OpenGLContext.h>
#include <chroma/events/KeyEvent.h>

namespace Chroma
{

    static bool s_GLFW_initialized = false;

    Window::Window(const WindowProps& props)
    {
        Init(props);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init(const WindowProps& props)
    {
        m_props = props;

        if (!s_GLFW_initialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            if (success == 0)
                CH_ERROR("Could not intialize GLFW!\n");
            //glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFW_initialized = true;
        }

        m_window_handle = glfwCreateWindow((int)props.m_window_width, (int)props.m_window_height, m_props.m_window_title.c_str(), nullptr, nullptr);

        m_context = new OpenGLContext(m_window_handle);
        m_context->Init();

        glfwSetWindowUserPointer(m_window_handle, &m_props);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_window_handle, [](GLFWwindow* window, int width, int height)
        {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
            data.m_window_width = width;
            data.m_window_height = height;

            /*WindowResizeEvent event(width, height);
            data.EventCallback(event);*/
        });

        /*glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });*/

        glfwSetKeyCallback(m_window_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                //data.EventCallback(event);
                CH_TRACE((event).ToString());
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                //data.EventCallback(event);
                CH_TRACE((event).ToString());
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                //data.EventCallback(event);
                CH_TRACE((event).ToString());
                break;
            }
            }
           //CH_TRACE( key );
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);
        });

        /*glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });*/

        /*glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });*/
    }


    void Window::Shutdown()
    {
        glfwDestroyWindow(m_window_handle);
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        m_context->SwapBuffers();
    }

    void Window::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_vsync = enabled;
    }

    bool Window::IsVSync() const
    {
        return m_vsync;
    }
}