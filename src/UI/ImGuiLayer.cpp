//
// Created by Andrew Graser on 11/17/2026.
//

#include "ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

#include <SDL3/SDL.h>


ImGuiLayer::ImGuiLayer(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer)
    : mSDLWindow(sdlWindow), mSDLRenderer(sdlRenderer)
{
    Init();
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Init()
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL3_InitForSDLRenderer(mSDLWindow, mSDLRenderer);
    ImGui_ImplSDLRenderer3_Init(mSDLRenderer);
}

void ImGuiLayer::ProcessEvent(const SDL_Event *event)
{
    ImGui_ImplSDL3_ProcessEvent(event);
}

void ImGuiLayer::Begin()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGui::End();

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), mSDLRenderer);
}
