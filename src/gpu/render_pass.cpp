// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/render_pass.hpp"

#include "jhoyt/mf/gpu/buffer.hpp"
#include "jhoyt/mf/gpu/command_buffer.hpp"
#include "jhoyt/mf/gpu/sampler.hpp"
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

    void render_pass::bind_index_buffer(const buffer &buffer, index_element_size index_element_size)
    {
        auto binding = SDL_GPUBufferBinding{.buffer = buffer.ptr(), .offset = 0};
        SDL_BindGPUIndexBuffer(ptr_, &binding, static_cast<SDL_GPUIndexElementSize>(index_element_size));
    }

    void render_pass::bind_fragment_sampler(uint32_t slot, const texture &texture, const sampler &sampler)
    {
        auto binding = SDL_GPUTextureSamplerBinding{.texture = texture.ptr(), .sampler = sampler.ptr()};
        SDL_BindGPUFragmentSamplers(ptr_, slot, &binding, 1);
    }

    void render_pass::draw_primitives(uint32_t num_vertices,
                                      uint32_t num_instance,
                                      uint32_t first_vertex,
                                      uint32_t first_instance)
    {
        SDL_DrawGPUPrimitives(ptr_, num_vertices, num_instance, first_vertex, first_instance);
    }

    void render_pass::draw_indexed_primitives(uint32_t num_indices,
                                              uint32_t num_instances,
                                              uint32_t first_index,
                                              int32_t vertex_offset,
                                              uint32_t first_instance)
    {
        SDL_DrawGPUIndexedPrimitives(ptr_, num_indices, num_instances, first_index, vertex_offset, first_instance);
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
