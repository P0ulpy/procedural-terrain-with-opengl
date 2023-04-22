//
// Created by Flo on 14/04/2023.
//

#include "Scene.hpp"


void Scene::Update(float dt)
{
    for (auto* updatable : m_updatables)
    {
        updatable->Update(dt);
    }
}

void Scene::Render(Camera& camera)
{
    for (auto* renderable : m_renderables)
    {
        renderable->Render(camera);
    }
}
