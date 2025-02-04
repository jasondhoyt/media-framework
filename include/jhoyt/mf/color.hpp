// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <algorithm>
#include <cstdint>

#include <SDL3/SDL_pixels.h>

namespace jhoyt::mf
{

    class color final
    {
    public:
        color() = default;

        color(float r, float g, float b, float a = 1.0f)
            : value_(std::clamp(r, 0.0f, 1.0f),
                     std::clamp(g, 0.0f, 1.0f),
                     std::clamp(b, 0.0f, 1.0f),
                     std::clamp(a, 0.0f, 1.0f))
        {
        }

        color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
            : value_(static_cast<float>(r) / 255.0f,
                     static_cast<float>(g) / 255.0f,
                     static_cast<float>(b) / 255.0f,
                     static_cast<float>(a) / 255.0f)
        {
        }

        auto r() const
        {
            return value_.r;
        }

        auto g() const
        {
            return value_.g;
        }

        auto b() const
        {
            return value_.b;
        }

        auto a() const
        {
            return value_.a;
        }

        const auto &sdl_color() const
        {
            return value_;
        }

    private:
        SDL_FColor value_ = {0.0f, 0.0f, 0.0f, 0.0f};
    };

} // namespace jhoyt::mf
