//
// Created by Flo on 14/04/2023.
//

#pragma once

#include <vector>
#include <memory>

#include "../Objects/IUpdatable.hpp"
#include "Renderable/IRenderable.hpp"

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;

    void Update(float dt);
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

        if constexpr (std::is_base_of_v<IRenderable, TObject>)
            std::remove(m_renderables.begin(), m_renderables.end(), object);

        std::remove(m_objects.begin(), m_objects.end(), object);
    }

protected:
    // Only purpose is to manage objects lifetime
    std::vector<std::unique_ptr<void, void(*)(void const*)>> m_objects;

    std::vector<IUpdatable*> m_updatables;
    std::vector<IRenderable*> m_renderables;
};
