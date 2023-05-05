//
// Created by Flo on 22/04/2023.
//

#include "UiWindow.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

UIWindow::UIWindow(const std::string_view& title, const ImVec2& size, ImGuiCond cond, ImGuiWindowFlags flags)
    : m_title(title)
    , m_size(size)
    , m_cond(cond)
    , m_flags(flags)
{

}

void UIWindow::OnGuiBegin()
{
    if(m_size.x > 0.f && m_size.y > 0.f)
        ImGui::SetNextWindowSize(m_size, m_cond);

    ImGui::Begin(m_title.c_str(), &m_isOpen, m_flags);
}

void UIWindow::OnGuiEnd()
{
    ImGui::End();
}