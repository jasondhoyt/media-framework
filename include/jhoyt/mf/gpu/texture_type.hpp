// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class texture_type
    {
        d2 = SDL_GPU_TEXTURETYPE_2D,
        d2_array = SDL_GPU_TEXTURETYPE_2D_ARRAY,
        d3 = SDL_GPU_TEXTURETYPE_3D,
        cube = SDL_GPU_TEXTURETYPE_CUBE,
        cube_array = SDL_GPU_TEXTURETYPE_CUBE_ARRAY
    };

}
