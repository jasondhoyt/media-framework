// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class index_element_size
    {
        bits_16 = SDL_GPU_INDEXELEMENTSIZE_16BIT,
        bits_32 = SDL_GPU_INDEXELEMENTSIZE_32BIT
    };

}
