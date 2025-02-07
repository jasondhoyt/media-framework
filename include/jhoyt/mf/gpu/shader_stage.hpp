// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class shader_stage
    {
        vertex = SDL_GPU_SHADERSTAGE_VERTEX,
        fragment = SDL_GPU_SHADERSTAGE_FRAGMENT
    };

}
