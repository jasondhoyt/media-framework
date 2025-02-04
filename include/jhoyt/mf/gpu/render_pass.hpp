// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "jhoyt/mf/color.hpp"

namespace jhoyt::mf::gpu
{

    class command_buffer;
    class texture;

    class render_pass final
    {
    public:
        render_pass(command_buffer &cmd_buf,
                    const texture &target,
                    const color &clear_color = {0.0f, 0.0f, 0.0f, 1.0f});
        ~render_pass();

        render_pass(const render_pass &) = delete;
        render_pass &operator=(const render_pass &) = delete;

        render_pass(render_pass &&) = delete;
        render_pass &operator=(render_pass &&) = delete;

        void end();

        auto ptr() const
        {
            return ptr_;
        }

    private:
        SDL_GPURenderPass *ptr_;
    };

} // namespace jhoyt::mf::gpu
