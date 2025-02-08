// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "../bit_flags.hpp"

namespace jhoyt::mf::gpu
{

    enum class texture_usage
    {
        sampler = SDL_GPU_TEXTUREUSAGE_SAMPLER,
        color_target = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET,
        depth_stencil_target = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
        graphics_storage_read = SDL_GPU_TEXTUREUSAGE_GRAPHICS_STORAGE_READ,
        compute_storage_read = SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_READ,
        compute_storage_write = SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_WRITE,
        compute_storage_simultaneous_read_write = SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_SIMULTANEOUS_READ_WRITE
    };

    using texture_usage_flags = bit_flags<texture_usage, uint32_t>;

} // namespace jhoyt::mf::gpu
