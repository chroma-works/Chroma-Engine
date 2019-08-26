#include <iostream>
#include <stdio.h>

#include <chroma/main/Log.h>
#include <chroma/main/Application.h>
#include <thirdparty/glm/glm/glm.hpp>

extern Chroma::Application* Chroma::CreateApplication();

int main(int argc, char const* argv[]) 
{
    Chroma::Log::Init();
    Chroma::Application* app = Chroma::CreateApplication();

    app->Run();
    delete app;
    return 0;
}