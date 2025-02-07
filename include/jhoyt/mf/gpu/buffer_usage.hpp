// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "../bit_flags.hpp"

namespace jhoyt::mf::gpu
{

    enum class buffer_usage
    {
        vertex = SDL_GPU_BUFFERUSAGE_VERTEX,
        index = SDL_GPU_BUFFERUSAGE_INDEX,
        indirect = SDL_GPU_BUFFERUSAGE_INDIRECT,
        graphics_storage_read = SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ,
        compute_storage_read = SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ,
        compute_storage_write = SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE
    };

    using buffer_usage_flags = bit_flags<buffer_usage, uint32_t>;

} // namespace jhoyt::mf::gpu
