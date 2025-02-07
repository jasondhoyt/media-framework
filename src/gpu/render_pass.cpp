// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/render_pass.hpp"

#include "jhoyt/mf/gpu/buffer.hpp"
#include "jhoyt/mf/gpu/command_buffer.hpp"
#include "jhoyt/mf/gpu/texture.hpp"

namespace jhoyt::mf::gpu
{

    render_pass::render_pass(SDL_GPUCommandBuffer *cmd_buf, SDL_GPUTexture *target, const color &clear_color)
    {
        auto info = SDL_GPUColorTargetInfo{0};
        info.texture = target;
        info.clear_color = clear_color.sdl_color();
        info.load_op = SDL_GPU_LOADOP_CLEAR;
        info.store_op = SDL_GPU_STOREOP_STORE;

        ptr_ = SDL_BeginGPURenderPass(cmd_buf, &info, 1, nullptr);
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    render_pass::~render_pass()
    {
        if (ptr_)
        {
            SDL_EndGPURenderPass(ptr_);
        }
    }

    void render_pass::bind_vertex_buffer(uint32_t slot, const buffer &buffer)
    {
        auto binding = SDL_GPUBufferBinding{.buffer = buffer.ptr(), .offset = 0};
        SDL_BindGPUVertexBuffers(ptr_, slot, &binding, 1);
    }

    void render_pass::draw_primitives(uint32_t num_vertices,
                                      uint32_t num_instance,
                                      uint32_t first_vertex,
                                      uint32_t first_instance)
    {
        SDL_DrawGPUPrimitives(ptr_, num_vertices, num_instance, first_vertex, first_instance);
    }

    void render_pass::end()
    {
        if (ptr_)
        {
            SDL_EndGPURenderPass(ptr_);
            ptr_ = nullptr;
        }
    }

} // namespace jhoyt::mf::gpu
