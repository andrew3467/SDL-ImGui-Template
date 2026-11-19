//
// Created by Andrew Graser on 11/17/2026.
//


#pragma once

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

class ImGuiLayer
{
public:
    ImGuiLayer(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);
    ~ImGuiLayer();

    void Init();

    void ProcessEvent(SDL_Event event) const;

    void Begin();
    void End();

private:
    SDL_Window *mSDLWindow;
    SDL_Renderer* mSDLRenderer;
};
