// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_pixels.h>

namespace jhoyt::mf
{

    enum class colorspace
    {
        unknown = SDL_COLORSPACE_UNKNOWN,
        srgb = SDL_COLORSPACE_SRGB,
        srgb_linear = SDL_COLORSPACE_SRGB_LINEAR,
        hdr10 = SDL_COLORSPACE_HDR10,
        jpeg = SDL_COLORSPACE_JPEG,
        bt601_limited = SDL_COLORSPACE_BT601_LIMITED,
        bt601_full = SDL_COLORSPACE_BT601_FULL,
        bt709_limited = SDL_COLORSPACE_BT709_LIMITED,
        bt709_full = SDL_COLORSPACE_BT709_FULL,
        bt2020_limited = SDL_COLORSPACE_BT2020_LIMITED,
        bt2020_full = SDL_COLORSPACE_BT2020_FULL,
        rgb_default = SDL_COLORSPACE_SRGB,
        yuv_default = SDL_COLORSPACE_JPEG
    };

}