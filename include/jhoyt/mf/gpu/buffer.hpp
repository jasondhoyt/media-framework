// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>

#include <SDL3/SDL_gpu.h>

#include "../fwd.hpp"
#include "buffer_usage.hpp"

namespace jhoyt::mf::gpu
{

    class device;

    class buffer final
    {
    public:
        static buffer_ptr create(device_ptr device, buffer_usage_flags usage, uint32_t size);

        ~buffer();

        buffer(const buffer &) = delete;
        buffer &operator=(const buffer &) = delete;

        buffer(buffer &&) = delete;
        buffer &operator=(buffer &&) = delete;

        auto size() const
        {
            return size_;
        }

        auto ptr() const
        {
            return ptr_;
        }

    private:
        device_ptr device_;
        SDL_GPUBuffer *ptr_;
        uint32_t size_;

        buffer(device_ptr device, SDL_GPUBuffer *ptr, uint32_t size);
    };

} // namespace jhoyt::mf::gpu
