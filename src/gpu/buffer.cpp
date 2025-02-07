// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/buffer.hpp"

#include "jhoyt/mf/gpu/device.hpp"

namespace jhoyt::mf::gpu
{

    buffer_ptr buffer::create(device_ptr device, buffer_usage_flags usage, uint32_t size)
    {
        assert(device);

        auto info = SDL_GPUBufferCreateInfo{.usage = usage.value(), .size = size};
        auto ptr = SDL_CreateGPUBuffer(device->ptr(), &info);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return buffer_ptr{new buffer(std::move(device), ptr, size)};
    }

    buffer::buffer(device_ptr device, SDL_GPUBuffer *ptr, uint32_t size)
        : device_(std::move(device)), ptr_(ptr), size_(size)
    {
    }

    buffer::~buffer()
    {
        SDL_ReleaseGPUBuffer(device_->ptr(), ptr_);
    }

} // namespace jhoyt::mf::gpu
