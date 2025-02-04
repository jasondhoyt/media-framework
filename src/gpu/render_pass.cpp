// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/render_pass.hpp"

#include "jhoyt/mf/gpu/command_buffer.hpp"
#include "jhoyt/mf/gpu/texture.hpp"

namespace jhoyt::mf::gpu
{

    render_pass::render_pass(command_buffer &cmd_buf, const texture &target, const color &clear_color)
    {
        auto info = SDL_GPUColorTargetInfo{0};
        info.texture = target.ptr();
        info.clear_color = clear_color.sdl_color();
        info.load_op = SDL_GPU_LOADOP_CLEAR;
        info.store_op = SDL_GPU_STOREOP_STORE;

        ptr_ = SDL_BeginGPURenderPass(cmd_buf.ptr(), &info, 1, nullptr);
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

    void render_pass::end()
    {
        if (ptr_)
        {
            SDL_EndGPURenderPass(ptr_);
            ptr_ = nullptr;
        }
    }

} // namespace jhoyt::mf::gpu
