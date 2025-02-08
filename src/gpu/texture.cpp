// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/texture.hpp"

#include "jhoyt/mf/gpu/device.hpp"

namespace jhoyt::mf::gpu
{

    texture_ptr texture::create(
        device_ptr device, texture_type type, texture_format format, texture_usage_flags usage, const class size &size)
    {
        assert(device);

        auto info = SDL_GPUTextureCreateInfo{.type = static_cast<SDL_GPUTextureType>(type),
                                             .format = static_cast<SDL_GPUTextureFormat>(format),
                                             .usage = usage.value(),
                                             .width = static_cast<uint32_t>(size.w()),
                                             .height = static_cast<uint32_t>(size.h()),
                                             .layer_count_or_depth = 1,
                                             .num_levels = 1,
                                             .sample_count = SDL_GPU_SAMPLECOUNT_1};
        auto ptr = SDL_CreateGPUTexture(device->ptr(), &info);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return texture_ptr{new texture(std::move(device), ptr, size)};
    }

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
