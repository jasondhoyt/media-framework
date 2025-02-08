// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class sampler_address_mode
    {
        repeat = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
        mirrored_repeat = SDL_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT,
        clamp_to_edge = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE
    };

}
