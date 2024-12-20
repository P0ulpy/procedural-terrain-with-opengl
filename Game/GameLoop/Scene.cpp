//
// Created by Flo on 14/04/2023.
//

#include <GameLoop/Scene.hpp>

void Scene::Update(float dt)
{
    for (auto* updatable : m_updatables)
    {
        updatable->Update(dt);
    }

    OnUpdate(dt);
}

void Scene::Render(Camera& camera)
{
    for (auto* renderable : m_renderables)
    {
        renderable->Render(camera);
    }
}

void Scene::OnGui()
{
    for (auto* widget : m_widgets)
    {
        widget->OnGui();
    }
}

Scene::~Scene()
{
    for(auto renderable : m_renderables)
    {
        renderable->Cleanup();
    }
}
