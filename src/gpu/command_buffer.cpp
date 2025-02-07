// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/command_buffer.hpp"

#include "jhoyt/mf/gpu/device.hpp"
#include "jhoyt/mf/gpu/graphics_pipeline.hpp"
#include "jhoyt/mf/window.hpp"

namespace jhoyt::mf::gpu
{

    command_buffer::command_buffer(SDL_GPUDevice *device) : ptr_(SDL_AcquireGPUCommandBuffer(device))
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    command_buffer::~command_buffer()
    {
        if (ptr_)
        {
            SDL_CancelGPUCommandBuffer(ptr_);
        }
    }

    void command_buffer::enqueue_copy_pass(std::function<void(copy_pass &)> fn)
    {
        if (!fn)
        {
            return;
        }

        auto cp = copy_pass{ptr_};
        fn(cp);
        cp.end();
    }

    void command_buffer::enqueue_render_pass(const window &window,
                                             const color &clear_color,
                                             std::function<void(render_pass &, const size &)> fn)
    {
        if (!fn)
        {
            return;
        }

        auto texture_ptr = static_cast<SDL_GPUTexture *>(nullptr);
        auto w = uint32_t{0};
        auto h = uint32_t{0};
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(ptr_, window.ptr(), &texture_ptr, &w, &h))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        if (texture_ptr)
        {
            auto rp = render_pass{ptr_, texture_ptr, clear_color};
            fn(rp, {static_cast<int>(w), static_cast<int>(h)});
            rp.end();
        }
    }

    void command_buffer::enqueue_render_pass(const window &window,
                                             const color &clear_color,
                                             const graphics_pipeline &pipeline,
                                             std::function<void(render_pass &, const size &)> fn)
    {
        if (!fn)
        {
            return;
        }

        auto texture_ptr = static_cast<SDL_GPUTexture *>(nullptr);
        auto w = uint32_t{0};
        auto h = uint32_t{0};
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(ptr_, window.ptr(), &texture_ptr, &w, &h))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        if (texture_ptr)
        {
            auto rp = render_pass{ptr_, texture_ptr, clear_color};
            SDL_BindGPUGraphicsPipeline(rp.ptr(), pipeline.ptr());
            fn(rp, {static_cast<int>(w), static_cast<int>(h)});
            rp.end();
        }
    }

    void command_buffer::submit()
    {
        if (ptr_)
        {
            SDL_SubmitGPUCommandBuffer(ptr_);
            ptr_ = nullptr;
        }
    }

} // namespace jhoyt::mf::gpu
