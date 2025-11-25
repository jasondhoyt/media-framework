// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_surface.h>

#include "bitflags.hpp"

namespace jhoyt::mf
{

    enum class flip_mode
    {
        none = SDL_FLIP_NONE,
        horizontal = SDL_FLIP_HORIZONTAL,
        vertical = SDL_FLIP_VERTICAL
    };

    using flip_mode_flags = bitflags<flip_mode, int>;

} // namespace jhoyt::mf