//
// Created by Andrew Graser on 11/17/2026.
//

#include "../src/SDLContext.h"

#include "SDL3/SDL.h"


SDLContext::SDLContext(int width, int height)
    : mWidth(width), mHeight(height)
{
    CreateContext();

    mImGuiContext = std::make_unique<ImGuiLayer>(mWindow, mRenderer);
}

SDLContext::~SDLContext()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

bool SDLContext::Render(const std::function<void()>& imguiCallback)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        mImGuiContext->ProcessEvent(event);

        if (event.type == SDL_EVENT_QUIT)
            return true;
    }

    SDL_SetRenderDrawColor(mRenderer, 30, 30, 30, 255);
    SDL_RenderClear(mRenderer);

    mImGuiContext->Begin();

    imguiCallback();

    mImGuiContext->End();

    SDL_RenderPresent(mRenderer);

    return false;
}

void SDLContext::CreateContext()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
    }

    mWindow = SDL_CreateWindow(
        "Neural Network",
        mWidth,
        mHeight,
        0
    );

    if (!mWindow)
    {
        SDL_Quit();
        throw std::runtime_error(std::string("Window Error: ") + SDL_GetError());
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        nullptr
    );

    if (!mRenderer)
    {
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        throw std::runtime_error(std::string("Failed to create renderer Error: ") + SDL_GetError());
    }
}