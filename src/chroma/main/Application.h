#pragma once

#include <chroma/events/Event.h>
#include <chroma/events/ApplicationEvent.h>
#include <chroma/window/Window.h>


namespace Chroma
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
        inline Window* GetWindow() { return m_window; }
        inline Application* Get() { return s_instance; }

    private:
        bool m_running = true;
        Window* m_window;

        static Application* s_instance;

        bool OnWindowClose(WindowCloseEvent& e);
    };
}