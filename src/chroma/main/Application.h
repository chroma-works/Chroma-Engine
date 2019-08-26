#pragma once

#include <chroma/events/ApplicationEvent.h>
#include <chroma/window/Window.h>
#include <chroma/renderer/LayerStack.h>


namespace Chroma
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();
        void PushLayer(Layer* layer);

        void OnEvent(Event& e);
        inline Window* GetWindow() { return m_window; }
        inline static Application& Get() { return *s_instance; }

    private:
        bool m_running = true;
        Window* m_window;

        static Application* s_instance;
        LayerStack m_layer_stack;
        float m_last_frame_time = 0.0f;

        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent & e);
    };

    Application* CreateApplication();
}