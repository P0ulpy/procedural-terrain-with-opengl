#include <UISystem/Widget.hpp>

Widget::~Widget()
{
    if(m_parent)
    {
        m_parent->RemoveChild(this);
    }

    for(auto& child : m_children)
    {
        child->SetParent(nullptr);
    }
}

void Widget::OnGui()
{
    OnGuiBegin();

    for(auto& child : m_children)
    {
        child->OnGui();
    }

    OnGuiEnd();
}

void Widget::AddChild(Widget *child)
{
    m_children.push_back(std::unique_ptr<Widget>(child));
}

void Widget::RemoveChild(Widget *child)
{
    auto it = std::find_if(m_children.begin(), m_children.end(), [child](const std::unique_ptr<Widget>& widget)
    {
        return widget.get() == child;
    });

    m_children.erase(it);
}
