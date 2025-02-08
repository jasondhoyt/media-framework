// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <stdexcept>

#include <SDL3/SDL_iostream.h>
#include <SDL3_image/SDL_image.h>

#include "jhoyt/mf/surface.hpp"

namespace jhoyt::mf
{

    surface::surface(const std::span<const uint8_t> &data)
    {
        auto stream = SDL_IOFromConstMem(data.data(), data.size());
        if (!stream)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        ptr_ = IMG_Load_IO(stream, true);
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    surface::~surface()
    {
        if (ptr_)
        {
            SDL_DestroySurface(ptr_);
        }
    }

    surface::surface(surface &&other) : ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
    }

    surface &surface::operator=(surface &&other)
    {
        if (this != &other)
        {
            if (ptr_)
            {
                SDL_DestroySurface(ptr_);
                ptr_ = nullptr;
            }

            std::swap(ptr_, other.ptr_);
        }

        return *this;
    }

    pixel_format surface::format() const
    {
        if (!ptr_)
        {
            return pixel_format::unknown;
        }

        return static_cast<pixel_format>(ptr_->format);
    }

    size surface::size() const
    {
        if (!ptr_)
        {
            return {};
        }

        return {ptr_->w, ptr_->h};
    }

    bool surface::convert_to_format(pixel_format format)
    {
        if (!ptr_)
        {
            return false;
        }

        if (ptr_->format == static_cast<SDL_PixelFormat>(format))
        {
            return false;
        }

        auto new_ptr = SDL_ConvertSurface(ptr_, static_cast<SDL_PixelFormat>(format));
        if (!new_ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        SDL_DestroySurface(ptr_);
        ptr_ = new_ptr;

        return true;
    }

} // namespace jhoyt::mf
