// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/device.hpp"

#include "jhoyt/mf/gpu/command_buffer.hpp"
#include "jhoyt/mf/window.hpp"

namespace jhoyt::mf::gpu
{

    std::shared_ptr<device> device::create(std::shared_ptr<context> ctx,
                                           shader_format_flags format_flags,
                                           bool debug_mode,
                                           const std::string &name)
    {
        assert(ctx);
        assert(format_flags.value() != 0);

        auto ptr = SDL_CreateGPUDevice(format_flags.value(), debug_mode, name.empty() ? nullptr : name.c_str());
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return std::shared_ptr<device>(new device(std::move(ctx), ptr));
    }

    device::device(std::shared_ptr<context> ctx, SDL_GPUDevice *ptr) : ctx_(std::move(ctx)), ptr_(ptr)
    {
    }

    device::~device()
    {
        for (const auto &window : windows_)
        {
            SDL_ReleaseWindowFromGPUDevice(ptr_, window->ptr());
        }

        SDL_DestroyGPUDevice(ptr_);
    }

    void device::claim_window(std::shared_ptr<window> window)
    {
        assert(window);

        if (!SDL_ClaimWindowForGPUDevice(ptr_, window->ptr()))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        windows_.push_back(std::move(window));
    }

    void device::release_window(const std::shared_ptr<window> &window)
    {
        assert(window);
        assert(std::find(std::begin(windows_), std::end(windows_), window) != windows_.end());

        SDL_ReleaseWindowFromGPUDevice(ptr_, window->ptr());
        std::erase(windows_, window);
    }

    texture_format device::swapchain_texture_format(const window &window)
    {
        return static_cast<texture_format>(SDL_GetGPUSwapchainTextureFormat(ptr_, window.ptr()));
    }

    void device::acquire_command_buffer(std::function<void(command_buffer &)> fn)
    {
        if (!fn)
        {
            return;
        }

        auto cmd_buf = command_buffer{ptr_};
        fn(cmd_buf);
        cmd_buf.submit();
    }

} // namespace jhoyt::mf::gpu
