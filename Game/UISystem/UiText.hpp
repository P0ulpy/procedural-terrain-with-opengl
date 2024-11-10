#pragma once

#include <string>
#include <string_view>
#include <UISystem/Widget.hpp>

class UIText : public Widget
{
public:
    UIText(const std::string_view& text);

    void SetText(const std::string_view& text) { m_text = text; }
    [[nodiscard]] const std::string& GetText() const { return m_text; }

protected:
    void OnGuiBegin() override;
    void OnGuiEnd() override;

private:
    std::string m_text;
};
