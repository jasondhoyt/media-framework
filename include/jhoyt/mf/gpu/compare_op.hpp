// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class compare_op
    {
        invalid = SDL_GPU_COMPAREOP_INVALID,
        never = SDL_GPU_COMPAREOP_NEVER,
        less = SDL_GPU_COMPAREOP_LESS,
        equal = SDL_GPU_COMPAREOP_EQUAL,
        less_or_equal = SDL_GPU_COMPAREOP_LESS_OR_EQUAL,
        greater = SDL_GPU_COMPAREOP_GREATER,
        not_equal = SDL_GPU_COMPAREOP_NOT_EQUAL,
        greater_or_equal = SDL_GPU_COMPAREOP_GREATER_OR_EQUAL,
        always = SDL_GPU_COMPAREOP_ALWAYS
    };

}
