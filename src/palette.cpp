// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/media-framework/palette.hpp"

namespace jhoyt::mf
{

    palette::palette(const int num_colors) : ptr_(SDL_CreatePalette(num_colors))
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    palette::palette(SDL_Palette* ptr, const bool auto_destroy) : ptr_(ptr), auto_destroy_(auto_destroy)
    {
    }

    palette::~palette()
    {
        destroy();
    }

    palette::palette(palette&& other) noexcept : ptr_(other.ptr_), auto_destroy_(other.auto_destroy_)
    {
        other.ptr_ = nullptr;
    }

    palette& palette::operator=(palette&& other) noexcept
    {
        if (this != &other)
        {
            destroy();

            std::swap(ptr_, other.ptr_);
            std::swap(auto_destroy_, other.auto_destroy_);
        }

        return *this;
    }

    void palette::destroy()
    {
        if (ptr_ && auto_destroy_)
        {
            SDL_DestroyPalette(ptr_);
        }

        ptr_ = nullptr;
    }

    std::span<const color> palette::get_colors() const
    {
        assert(ptr_);
        return {static_cast<const color*>(ptr_->colors), static_cast<size_t>(ptr_->ncolors)};
    }

    std::span<color> palette::get_colors()
    {
        assert(ptr_);
        return {static_cast<color*>(ptr_->colors), static_cast<size_t>(ptr_->ncolors)};
    }

    color palette::get_color(const int ix) const
    {
        assert(ptr_);

        if (ix >= 0 && ix < ptr_->ncolors)
        {
            return {ptr_->colors[ix]};
        }

        return {0};
    }

    void palette::set_color(const int ix, const color& color)
    {
        assert(ptr_);

        if (ix >= 0 && ix < ptr_->ncolors)
        {
            ptr_->colors[ix] = color;
        }
    }

} // namespace jhoyt::mf