#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <chroma/renderer/RenderContext.h>
#include <functional>
#include <chroma/events/Event.h>

namespace Chroma
{
    struct WindowData
    {
        int Width;
        int Height;
        std::string Title;

        std::function<void(Event&)> EventCallback;
    };
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
        Window(const WindowProps& props);
        virtual ~Window();

        inline int GetWidth() { return m_data.Width; }
        inline int GetHeight() { return m_data.Height; }

        void OnUpdate();

        inline void SetEventCallback(std::function<void(Event&)> callback) { m_data.EventCallback = callback; }

        void SetVSync(bool enabled);
        bool IsVSync() const;

    private:
        GLFWwindow* m_window_handle;
        RenderContext* m_context;
        bool m_vsync;


        WindowData m_data;


        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };
}