//
// Created by Flo on 05/05/2023.
//

#include "UiButton.hpp"

UIButton::UIButton(const std::string_view &text, const ImVec2 &size)
    : m_text(text)
    , m_size(size)
{

}

void UIButton::OnGuiBegin()
{
    if (ImGui::Button(m_text.c_str(), m_size))
    {
        if (m_clickCallback)
            m_clickCallback();
    }
}

void UIButton::OnGuiEnd()
{

}
