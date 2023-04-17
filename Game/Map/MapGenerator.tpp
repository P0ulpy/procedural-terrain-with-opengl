//
// Created by Flo on 17/04/2023.
//

#pragma once

template<typename T>
void MapGenerator::Render(const Mat4<T> &viewProjection)
{
    m_triangle.Render(viewProjection);
}
