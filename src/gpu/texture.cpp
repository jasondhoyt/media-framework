// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/texture.hpp"

#include "jhoyt/mf/gpu/device.hpp"

namespace jhoyt::mf::gpu
{

    texture::texture(device_ptr device, SDL_GPUTexture *ptr, const class size &size)
        : device_(std::move(device)), ptr_(ptr), size_(size)
    {
    }

    texture::~texture()
    {
        if (ptr_ && device_)
        {
            SDL_ReleaseGPUTexture(device_->ptr(), ptr_);
        }
    }

} // namespace jhoyt::mf::gpu
