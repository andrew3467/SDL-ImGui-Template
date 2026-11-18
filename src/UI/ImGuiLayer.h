//
// Created by Andrew Graser on 11/17/2026.
//


#pragma once
#include "imgui.h"

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

class ImGuiLayer
{
public:
    ImGuiLayer(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);
    ~ImGuiLayer();

    void Init();

    void ProcessEvent(const SDL_Event *event);

    void Begin();
    void End();

private:
    SDL_Window *mSDLWindow;
    SDL_Renderer* mSDLRenderer;
};
