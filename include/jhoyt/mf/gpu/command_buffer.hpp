// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>

#include <SDL3/SDL_gpu.h>

#include "texture.hpp"

namespace jhoyt::mf
{

    class window;

    namespace gpu
    {

        class device;

        class command_buffer final
        {
        public:
            command_buffer(std::shared_ptr<device> device);
            ~command_buffer();

            command_buffer(const command_buffer &) = delete;
            command_buffer &operator=(const command_buffer &) = delete;

            command_buffer(command_buffer &&other);
            command_buffer &operator=(command_buffer &&other);

            texture wait_and_acquire_swapchain_texture(const window &window);

            void submit();

            auto ptr() const
            {
                return ptr_;
            }

        private:
            std::shared_ptr<device> device_;
            SDL_GPUCommandBuffer *ptr_;
        };

    } // namespace gpu

} // namespace jhoyt::mf
