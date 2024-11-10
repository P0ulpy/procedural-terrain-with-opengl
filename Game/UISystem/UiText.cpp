#include <imgui.h>
#include <UISystem/UiText.hpp>

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
