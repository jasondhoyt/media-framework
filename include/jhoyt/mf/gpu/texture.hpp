// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>

#include <SDL3/SDL_gpu.h>

#include "../size.hpp"

namespace jhoyt::mf::gpu
{

    class device;

    class texture final
    {
    public:
        friend class command_buffer;

        ~texture();

        texture(const texture &) = delete;
        texture &operator=(const texture &) = delete;

        texture(texture &&other);
        texture &operator=(texture &&other);

        operator bool() const
        {
            return ptr_ != nullptr;
        }

        const auto &size() const
        {
            return size_;
        }

        auto ptr() const
        {
            return ptr_;
        }

    private:
        std::shared_ptr<device> device_;
        SDL_GPUTexture *ptr_;
        class size size_;

        texture(SDL_GPUTexture *ptr, const class size &size);
    };

} // namespace jhoyt::mf::gpu
