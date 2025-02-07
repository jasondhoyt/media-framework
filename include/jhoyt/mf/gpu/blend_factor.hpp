// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class blend_factor
    {
        invalid = SDL_GPU_BLENDFACTOR_INVALID,
        zero = SDL_GPU_BLENDFACTOR_ZERO,
        one = SDL_GPU_BLENDFACTOR_ONE,
        src_color = SDL_GPU_BLENDFACTOR_SRC_COLOR,
        one_minus_src_color = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
        dst_color = SDL_GPU_BLENDFACTOR_DST_COLOR,
        one_minus_dst_color = SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_COLOR,
        src_alpha = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
        one_minus_src_alpha = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
        dst_alpha = SDL_GPU_BLENDFACTOR_DST_ALPHA,
        one_minus_dst_alpha = SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
        constant_color = SDL_GPU_BLENDFACTOR_CONSTANT_COLOR,
        one_minus_constant_color = SDL_GPU_BLENDFACTOR_ONE_MINUS_CONSTANT_COLOR,
        src_alpha_saturate = SDL_GPU_BLENDFACTOR_SRC_ALPHA_SATURATE
    };

}
