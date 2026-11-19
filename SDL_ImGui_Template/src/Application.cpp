//
// Created by Andrew Graser on 11/17/2026.
//

#include "Application.h"

#include "Sandbox.h"
#include "../src/SDLContext.h"


Application::Application()
{

}

void Application::Run()
{
    SDLContext sdlContext(1280, 720);

    SandBox sandbox {};


    sandbox.Start();
    while (!sdlContext.Render(
        [&sandbox]()
        {
            sandbox.OnImGuiRender();
        }
    ))
    {
        sandbox.Update();
    }
}
