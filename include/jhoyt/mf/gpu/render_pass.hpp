// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "jhoyt/mf/color.hpp"

namespace jhoyt::mf::gpu
{

    class buffer;

    class render_pass final
    {
    public:
        ~render_pass();

        render_pass(const render_pass &) = delete;
        render_pass &operator=(const render_pass &) = delete;

        render_pass(render_pass &&) = delete;
        render_pass &operator=(render_pass &&) = delete;

        void bind_vertex_buffer(uint32_t slot, const buffer &buffer);

        void draw_primitives(uint32_t num_vertices,
                             uint32_t num_instance = 1,
                             uint32_t first_vertex = 0,
                             uint32_t first_instance = 0);

        auto ptr() const
        {
            return ptr_;
        }

        friend class command_buffer;

    private:
        SDL_GPURenderPass *ptr_;

        render_pass(SDL_GPUCommandBuffer *cmd_buf, SDL_GPUTexture *target, const color &clear_color);
        void end();
    };

} // namespace jhoyt::mf::gpu
