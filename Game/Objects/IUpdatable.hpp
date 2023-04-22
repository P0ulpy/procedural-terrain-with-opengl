//
// Created by Flo on 20/04/2023.
//

#pragma once

class IUpdatable
{
public:
    virtual ~IUpdatable() = default;

    virtual void Update(float dt) = 0;
};