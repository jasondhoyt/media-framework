// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_surface.h>

namespace jhoyt::mf
{

    enum class scale_mode
    {
        invalid = SDL_SCALEMODE_INVALID,
        nearest = SDL_SCALEMODE_NEAREST,
        linear = SDL_SCALEMODE_LINEAR
    };

}