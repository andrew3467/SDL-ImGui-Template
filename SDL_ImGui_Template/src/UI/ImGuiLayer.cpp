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

void ImGuiLayer::ProcessEvent(SDL_Event event) const
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void ImGuiLayer::Begin()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    //window_flags |= ImGuiWindowFlags_MenuBar;

    //Docking Space
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    if(dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
        window_flags |= ImGuiWindowFlags_NoBackground;
    }

    int width, height;
    SDL_GetWindowSize(mSDLWindow, &width, &height);
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
    ImGui::Begin("Dockspace", nullptr, window_flags);
    ImGui::PopStyleVar(2);
    ImGuiID dockspace_id = ImGui::GetID("Dockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    ImGui::End();
}

void ImGuiLayer::End()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), mSDLRenderer);
}
