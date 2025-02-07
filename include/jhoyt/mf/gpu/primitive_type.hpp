// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class primitive_type
    {
        triangle_list = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        triangle_strip = SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP,
        line_list = SDL_GPU_PRIMITIVETYPE_LINELIST,
        line_strip = SDL_GPU_PRIMITIVETYPE_LINESTRIP,
        point_list = SDL_GPU_PRIMITIVETYPE_POINTLIST
    };

}
