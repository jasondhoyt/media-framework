// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "../bit_flags.hpp"

namespace jhoyt::mf::gpu
{

    enum class color_component
    {
        red = SDL_GPU_COLORCOMPONENT_R,
        green = SDL_GPU_COLORCOMPONENT_G,
        blue = SDL_GPU_COLORCOMPONENT_B,
        alpha = SDL_GPU_COLORCOMPONENT_A
    };

    using color_component_flags = bit_flags<color_component, uint8_t>;

} // namespace jhoyt::mf::gpu
