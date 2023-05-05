//
// Created by Flo on 14/04/2023.
//

#pragma once

#include <vector>
#include <memory>

#include "../Objects/IUpdatable.hpp"
#include "Renderable/IRenderable.hpp"
#include "../UISystem/Widget.hpp"

class Scene
{
public:
    virtual ~Scene();
    virtual void Init() = 0;

    void Update(float dt);
    void OnGui();
    void Render(Camera& camera);

    template <class TObject>
    void AddObject(TObject* object)
    {
        m_objects.push_back(
            std::unique_ptr<void, void(*)(void const*)>(
                static_cast<void*>(object),
                [](void const * data)
                {
                    auto const* p = static_cast<TObject const*>(data);
                    delete p;
                })
        );

        if constexpr (std::is_base_of_v<IUpdatable, TObject>)
            m_updatables.push_back(object);

        if constexpr (std::is_base_of_v<Widget, TObject>)
            m_widgets.push_back(object);

        if constexpr (std::is_base_of_v<IRenderable, TObject>)
        {
            object->Load();
            m_renderables.push_back(object);
        }
    }

    template <class TObject>
    void RemoveObject(TObject* object)
    {
        if constexpr (std::is_base_of_v<IUpdatable, TObject>)
            std::remove(m_updatables.begin(), m_updatables.end(), object);

        if constexpr (std::is_base_of_v<Widget, TObject>)
            std::remove(m_widgets.begin(), m_widgets.end(), object);

        if constexpr (std::is_base_of_v<IRenderable, TObject>)
        {
            object->Cleanup();
            std::remove(m_renderables.begin(), m_renderables.end(), object);
        }

        std::remove(m_objects.begin(), m_objects.end(), object);
    }

protected:
    virtual void OnUpdate(float deltaTime) {};

protected:
    // Only purpose is to manage objects lifetime
    std::vector<std::unique_ptr<void, void(*)(void const*)>> m_objects;

    std::vector<IUpdatable*> m_updatables;
    std::vector<Widget*> m_widgets;
    std::vector<IRenderable*> m_renderables;
};
