// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class vertex_input_rate
    {
        vertex = SDL_GPU_VERTEXINPUTRATE_VERTEX,
        instance = SDL_GPU_VERTEXINPUTRATE_INSTANCE
    };

}
