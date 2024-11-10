#pragma once

class IUpdatable
{
public:
    virtual ~IUpdatable() = default;

    virtual void Update(float dt) = 0;
};