//
// Created by Flo on 05/05/2023.
//

#include "UiText.hpp"
#include <imgui.h>

UIText::UIText(const std::string_view &text)
        : m_text(text)
{}

void UIText::OnGuiBegin()
{
    ImGui::TextUnformatted(m_text.c_str());
}

void UIText::OnGuiEnd()
{

}
