#pragma once

#include <iostream>
#include <stdio.h>

#include <chroma/main/Log.h>
#include <chroma/main/Application.h>
#include <thirdparty/glm/glm/glm.hpp>

int main(int argc, char** argv)
{
    Chroma::Log::Init();
    Chroma::Application* app = new Chroma::Application();

    app->Run();
    delete app;
    return 0;
}