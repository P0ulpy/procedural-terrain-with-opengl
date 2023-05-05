//
// Created by Flo on 05/05/2023.
//

#pragma once

#include <string>
#include <functional>

#include <imgui.h>

#include "Widget.hpp"

class UISliderFloat : public Widget
{
public:
    UISliderFloat(const std::string_view& label, float value, float min, float max)
        : m_label(label), m_value(value), m_min(min), m_max(max)
    {}

    void OnGuiBegin() override
    {
        if(ImGui::SliderFloat(m_label.c_str(), &m_value, m_min, m_max))
        {
            if(m_onValueChangeCallback)
                m_onValueChangeCallback(m_value);
        }
    }

    void OnGuiEnd() override
    {

    }

    void SetOnValueChange(std::function<void(float)> callback) { m_onValueChangeCallback = callback; }

private:
    std::string m_label;
    float m_value;
    float m_min;
    float m_max;

    std::function<void(float)> m_onValueChangeCallback;
};
