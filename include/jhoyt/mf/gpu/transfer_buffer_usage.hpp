// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    enum class transfer_buffer_usage
    {
        upload = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        download = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD
    };

}
