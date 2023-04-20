//
// Created by Flo on 20/04/2023.
//

#pragma once

#include "IRender.hpp"

class Cube : public IRender
{
public:
    Cube();

    void Load() override;
    void Render() override;
};
