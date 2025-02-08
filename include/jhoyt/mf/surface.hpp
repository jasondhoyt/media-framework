// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <span>

#include <SDL3/SDL_surface.h>

#include "pixel_format.hpp"
#include "size.hpp"

namespace jhoyt::mf
{

    class surface final
    {
    public:
        surface() = default;
        surface(const std::span<const uint8_t> &data);

        ~surface();

        surface(const surface &) = delete;
        surface &operator=(const surface &) = delete;

        surface(surface &&other);
        surface &operator=(surface &&other);

        size size() const;

        pixel_format format() const;

        bool convert_to_format(pixel_format format);

        auto ptr() const
        {
            return ptr_;
        }

    private:
        SDL_Surface *ptr_ = nullptr;
    };

} // namespace jhoyt::mf
