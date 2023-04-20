#pragma once

template<typename T>
void MapGenerator::Render(const Mat4<T> &viewProjection)
{
    m_terrain.Render(viewProjection);
}
