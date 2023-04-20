//
// Created by Flo on 17/04/2023.
//

#pragma once

class IRender
{
public:
    virtual ~IRender() = default;

    virtual void Load() = 0;
    virtual void Render() = 0;
};
