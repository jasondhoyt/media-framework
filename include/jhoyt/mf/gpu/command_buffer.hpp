// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <functional>
#include <memory>
#include <utility>

#include <SDL3/SDL_gpu.h>

#include "../color.hpp"
#include "../fwd.hpp"
#include "../size.hpp"
#include "copy_pass.hpp"
#include "render_pass.hpp"

namespace jhoyt::mf
{

    class window;

    namespace gpu
    {

        class command_buffer final
        {
        public:
            ~command_buffer();

            command_buffer(const command_buffer &) = delete;
            command_buffer &operator=(const command_buffer &) = delete;

            command_buffer(command_buffer &&) = delete;
            command_buffer &operator=(command_buffer &&) = delete;

            void enqueue_copy_pass(std::function<void(copy_pass &)> fn);

            void enqueue_render_pass(const window &window,
                                     const color &clear_color,
                                     std::function<void(render_pass &, const size &)> fn);

            void enqueue_render_pass(const window &window,
                                     const color &clear_color,
                                     const graphics_pipeline &pipeline,
                                     std::function<void(render_pass &, const size &)> fn);

            auto ptr() const
            {
                return ptr_;
            }

            friend class device;

        private:
            SDL_GPUCommandBuffer *ptr_;

            command_buffer(SDL_GPUDevice *device);
            void submit();
        };

    } // namespace gpu

} // namespace jhoyt::mf
