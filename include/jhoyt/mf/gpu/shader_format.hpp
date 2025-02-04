// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "../bit_flags.hpp"

namespace jhoyt::mf::gpu
{

    enum class shader_format
    {
        invalid = SDL_GPU_SHADERFORMAT_INVALID,
        reserved = SDL_GPU_SHADERFORMAT_PRIVATE,
        spirv = SDL_GPU_SHADERFORMAT_SPIRV,
        dxbc = SDL_GPU_SHADERFORMAT_DXBC,
        dxil = SDL_GPU_SHADERFORMAT_DXIL,
        msl = SDL_GPU_SHADERFORMAT_MSL,
        metallib = SDL_GPU_SHADERFORMAT_METALLIB
    };

    using shader_format_flags = bit_flags<shader_format, uint32_t>;

} // namespace jhoyt::mf::gpu
