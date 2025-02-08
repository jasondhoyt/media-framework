// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class filter
    {
        nearest = SDL_GPU_FILTER_NEAREST,
        linear = SDL_GPU_FILTER_LINEAR
    };

}
