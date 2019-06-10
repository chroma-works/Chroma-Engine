#include <iostream>
#include <stdio.h>

#include "chroma/window/Window.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(int argc, char const* argv[]) 
{
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

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}