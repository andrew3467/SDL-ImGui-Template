//
// Created by Andrew Graser on 11/17/2026.
//


#pragma once

#include <functional>
#include <memory>

#include "UI/ImGuiLayer.h"


struct SDL_Window;
struct SDL_Renderer;

class SDLContext
{
public:
    SDLContext(int width, int height);
    ~SDLContext();

    bool Render(const std::function<void()>& imguiCallback);

private:
    void CreateContext();

private:
    int mWidth, mHeight;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    std::unique_ptr<ImGuiLayer> mImGuiContext;
};
