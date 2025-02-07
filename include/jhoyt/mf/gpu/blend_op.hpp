// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class blend_op
    {
        invalid = SDL_GPU_BLENDOP_INVALID,
        add = SDL_GPU_BLENDOP_ADD,
        subtract = SDL_GPU_BLENDOP_SUBTRACT,
        reverse_subtract = SDL_GPU_BLENDOP_REVERSE_SUBTRACT,
        min = SDL_GPU_BLENDOP_MIN,
        max = SDL_GPU_BLENDOP_MAX
    };

}
