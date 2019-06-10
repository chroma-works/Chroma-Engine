#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <chroma/renderer/RenderContext.h>

namespace Chroma
{
    struct WindowProps
    {
        std::string m_window_title;
        int m_window_width;
        int m_window_height;

        WindowProps(const std::string& title = "Chroma-Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : m_window_title(title), m_window_width(width), m_window_height(height)
        {}
    };
    class Window
    {
    public:
        GLFWwindow* m_window_handle;

        Window(const WindowProps& props);
        virtual ~Window();

        inline int GetWidth() { return m_props.m_window_width; }
        inline int GetHeight() { return m_props.m_window_height; }

        void OnUpdate();

        //inline void SetEventCallback(void* callback) { m_event_call_back = callback; }

        void SetVSync(bool enabled);
        bool IsVSync() const;

    private:
        WindowProps m_props;
        RenderContext* m_context;
        bool m_vsync;


        void* m_event_call_back;



        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };
}