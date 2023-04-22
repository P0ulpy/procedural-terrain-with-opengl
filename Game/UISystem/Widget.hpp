//
// Created by Flo on 22/04/2023.
//

#pragma once

#include <vector>
#include <memory>

#include "../Objects/IUpdatable.hpp"

class Widget : public IUpdatable
{
public:
    Widget() = default;
    ~Widget() override;

    void Update(float dt) override;
    void SetParent(Widget* parent) { m_parent = parent; }
    void AddChild(Widget* child);
    void RemoveChild(Widget* child);

protected:
    virtual void OnGuiBegin() = 0;
    virtual void OnGuiEnd() = 0;

protected:
    Widget* m_parent { nullptr };
    std::vector<std::unique_ptr<Widget>> m_children;
};
