#pragma once

#include <string>
#include <functional>

#include <imgui.h>

#include <UISystem/Widget.hpp>

class UISliderInt : public Widget
{
public:
    UISliderInt(const std::string_view& label, int value, int min, int max)
        : m_label(label), m_value(value), m_min(min), m_max(max)
    {}

    void OnGuiBegin() override
    {
        if(ImGui::SliderInt(m_label.c_str(), &m_value, m_min, m_max))
        {
            if(m_onValueChangeCallback)
                m_onValueChangeCallback(m_value);
        }
    }

    void OnGuiEnd() override
    {

    }

    void SetOnValueChange(std::function<void(int)> callback) { m_onValueChangeCallback = callback; }

private:
    std::string m_label;
    int m_value;
    int m_min;
    int m_max;

    std::function<void(int)> m_onValueChangeCallback;
};
