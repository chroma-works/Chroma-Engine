#include <iostream>
#include <stdio.h>

#include "chroma/window/Window.h"
#include <chroma/main/Log.h>

int main(int argc, char const* argv[]) 
{
    Chroma::Log::Init();
    Chroma::WindowProps props = Chroma::WindowProps();
    Chroma::Window* window = new Chroma::Window(props);

    // Main loop
    while (!glfwWindowShouldClose(window->m_window_handle))
    {
        //glClearColor(0.184f, 0.062f, 0.129f, 1.0f);
        window->OnUpdate();
    }

    return 0;
}