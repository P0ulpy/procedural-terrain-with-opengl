//
// Created by Flo on 22/04/2023.
//

#pragma once

#include <string>
#include <string_view>
#include <imgui.h>

#include "Widget.hpp"

class UIWindow : public Widget
{
public:
    UIWindow();
    UIWindow(const std::string_view& title, const ImVec2& size = {0, 0}, ImGuiCond cond = 0, ImGuiWindowFlags flags = 0);

    [[nodiscard]] bool IsOpen() const { return m_isOpen; }

protected:
    void OnGuiBegin() override;
    void OnGuiEnd() override;

protected:
    std::string m_title;
    ImVec2 m_size { 0.f, 0.f };
    ImGuiCond m_cond = 0;
    ImGuiWindowFlags m_flags = 0;

    bool m_isOpen { true };
};
