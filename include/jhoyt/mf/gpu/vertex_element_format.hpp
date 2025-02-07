// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class vertex_element_format
    {
        invalid = SDL_GPU_VERTEXELEMENTFORMAT_INVALID,

        /* 32-bit Signed Integers */
        int1 = SDL_GPU_VERTEXELEMENTFORMAT_INT,
        int2 = SDL_GPU_VERTEXELEMENTFORMAT_INT2,
        int3 = SDL_GPU_VERTEXELEMENTFORMAT_INT3,
        int4 = SDL_GPU_VERTEXELEMENTFORMAT_INT4,

        /* 32-bit Unsigned Integers */
        uint1 = SDL_GPU_VERTEXELEMENTFORMAT_UINT,
        uint2 = SDL_GPU_VERTEXELEMENTFORMAT_UINT2,
        uint3 = SDL_GPU_VERTEXELEMENTFORMAT_UINT3,
        uint4 = SDL_GPU_VERTEXELEMENTFORMAT_UINT4,

        /* 32-bit Floats */
        float1 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT,
        float2 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
        float3 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
        float4 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,

        /* 8-bit Signed Integers */
        byte2 = SDL_GPU_VERTEXELEMENTFORMAT_BYTE2,
        byte4 = SDL_GPU_VERTEXELEMENTFORMAT_BYTE4,

        /* 8-bit Unsigned Integers */
        ubyte2 = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2,
        ubyte4 = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4,

        /* 8-bit Signed Normalized */
        byte2_norm = SDL_GPU_VERTEXELEMENTFORMAT_BYTE2_NORM,
        byte4_norm = SDL_GPU_VERTEXELEMENTFORMAT_BYTE4_NORM,

        /* 8-bit Unsigned Normalized */
        ubyte2_norm = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2_NORM,
        ubyte4_norm = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM,

        /* 16-bit Signed Integers */
        short2 = SDL_GPU_VERTEXELEMENTFORMAT_SHORT2,
        short4 = SDL_GPU_VERTEXELEMENTFORMAT_SHORT4,

        /* 16-bit Unsigned Integers */
        ushort2 = SDL_GPU_VERTEXELEMENTFORMAT_USHORT2,
        ushort4 = SDL_GPU_VERTEXELEMENTFORMAT_USHORT4,

        /* 16-bit Signed Normalized */
        short2_norm = SDL_GPU_VERTEXELEMENTFORMAT_SHORT2_NORM,
        short4_norm = SDL_GPU_VERTEXELEMENTFORMAT_SHORT4_NORM,

        /* 16-bit Unsigned Normalized */
        ushort2_norm = SDL_GPU_VERTEXELEMENTFORMAT_USHORT2_NORM,
        ushort4_norm = SDL_GPU_VERTEXELEMENTFORMAT_USHORT4_NORM,

        /* 16-bit Floats */
        half2 = SDL_GPU_VERTEXELEMENTFORMAT_HALF2,
        half4 = SDL_GPU_VERTEXELEMENTFORMAT_HALF4
    };

}
