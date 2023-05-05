//
// Created by Flo on 05/05/2023.
//

#pragma once


#include "Widget.hpp"
#include <imgui.h>
#include <string_view>
#include <functional>

class UIButton : public Widget
{
public:
    UIButton(const std::string_view& text, const ImVec2& size = {0, 0});

    void SetOnClick(std::function<void()> callback) { m_clickCallback = callback; }

protected:
    void OnGuiBegin() override;
    void OnGuiEnd() override;

private:
    std::string m_text;
    ImVec2 m_size { 0.f, 0.f };

    std::function<void()> m_clickCallback;
};
