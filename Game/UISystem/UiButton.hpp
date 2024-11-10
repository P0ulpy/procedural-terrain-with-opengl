#pragma once

#include <imgui.h>
#include <string_view>
#include <functional>

#include <UISystem/Widget.hpp>

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
