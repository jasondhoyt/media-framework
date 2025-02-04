// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/command_buffer.hpp"

#include "jhoyt/mf/gpu/device.hpp"
#include "jhoyt/mf/window.hpp"

namespace jhoyt::mf::gpu
{

    command_buffer::command_buffer(std::shared_ptr<device> device) : device_(std::move(device))
    {
        assert(device_);

        ptr_ = SDL_AcquireGPUCommandBuffer(device_->ptr());
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

    command_buffer::command_buffer(command_buffer &&other) : device_(std::move(other.device_)), ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
    }

    command_buffer &command_buffer::operator=(command_buffer &&other)
    {
        if (this != &other)
        {
            if (ptr_)
            {
                SDL_CancelGPUCommandBuffer(ptr_);
                ptr_ = nullptr;
            }
            device_.reset();

            std::swap(device_, other.device_);
            std::swap(ptr_, other.ptr_);
        }

        return *this;
    }

    texture command_buffer::wait_and_acquire_swapchain_texture(const window &window)
    {
        if (!ptr_)
        {
            return {nullptr, {}};
        }

        auto texture_ptr = static_cast<SDL_GPUTexture *>(nullptr);
        auto w = uint32_t{0};
        auto h = uint32_t{0};
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(ptr_, window.ptr(), &texture_ptr, &w, &h))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {texture_ptr, {static_cast<int>(w), static_cast<int>(h)}};
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
