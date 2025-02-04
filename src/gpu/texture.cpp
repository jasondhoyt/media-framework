// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/texture.hpp"

#include "jhoyt/mf/gpu/device.hpp"

namespace jhoyt::mf::gpu
{

    texture::texture(SDL_GPUTexture *ptr, const class size &size) : ptr_(ptr), size_(size)
    {
    }

    texture::~texture()
    {
        if (ptr_ && device_)
        {
            SDL_ReleaseGPUTexture(device_->ptr(), ptr_);
        }
    }

    texture::texture(texture &&other) : device_(std::move(other.device_)), ptr_(other.ptr_), size_(other.size_)
    {
        other.ptr_ = nullptr;
        other.size_ = {};
    }

    texture &texture::operator=(texture &&other)
    {
        if (this != &other)
        {
            if (ptr_)
            {
                if (device_)
                {
                    SDL_ReleaseGPUTexture(device_->ptr(), ptr_);
                    device_.reset();
                }

                ptr_ = nullptr;
                size_ = {};
            }

            std::swap(device_, other.device_);
            std::swap(ptr_, other.ptr_);
            std::swap(size_, other.size_);
        }

        return *this;
    }

} // namespace jhoyt::mf::gpu
