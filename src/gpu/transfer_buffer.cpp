// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/transfer_buffer.hpp"

#include "jhoyt/mf/gpu/buffer.hpp"
#include "jhoyt/mf/gpu/copy_pass.hpp"
#include "jhoyt/mf/gpu/device.hpp"
#include "jhoyt/mf/gpu/texture.hpp"

#include "jhoyt/mf/surface.hpp"

namespace jhoyt::mf::gpu
{

    transfer_buffer_ptr transfer_buffer::create(device_ptr device, transfer_buffer_usage usage, uint32_t size)
    {
        assert(device);

        auto info =
            SDL_GPUTransferBufferCreateInfo{.usage = static_cast<SDL_GPUTransferBufferUsage>(usage), .size = size};
        auto ptr = SDL_CreateGPUTransferBuffer(device->ptr(), &info);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return transfer_buffer_ptr{new transfer_buffer(std::move(device), ptr, size)};
    }

    transfer_buffer::transfer_buffer(device_ptr device, SDL_GPUTransferBuffer *ptr, uint32_t size)
        : device_(std::move(device)), ptr_(ptr), size_(size)
    {
    }

    transfer_buffer::~transfer_buffer()
    {
        SDL_ReleaseGPUTransferBuffer(device_->ptr(), ptr_);
    }

    void transfer_buffer::copy_data(const std::span<const uint8_t> &data, bool cycle)
    {
        auto max_bytes_to_copy = static_cast<uint32_t>(data.size());
        if (max_bytes_to_copy > size_)
        {
            max_bytes_to_copy = size_;
        }

        auto ptr = SDL_MapGPUTransferBuffer(device_->ptr(), ptr_, cycle);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        memcpy(ptr, data.data(), max_bytes_to_copy);

        SDL_UnmapGPUTransferBuffer(device_->ptr(), ptr_);
    }

    void transfer_buffer::copy_data(const surface &surface, bool cycle)
    {
        auto sdl_surface = surface.ptr();
        if (!sdl_surface)
        {
            return;
        }

        auto max_bytes_to_copy = static_cast<uint32_t>(sdl_surface->w * sdl_surface->h * 4);
        if (max_bytes_to_copy > size_)
        {
            max_bytes_to_copy = size_;
        }

        auto ptr = SDL_MapGPUTransferBuffer(device_->ptr(), ptr_, cycle);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        memcpy(ptr, sdl_surface->pixels, max_bytes_to_copy);

        SDL_UnmapGPUTransferBuffer(device_->ptr(), ptr_);
    }

    void transfer_buffer::upload(const copy_pass &copy_pass, const buffer &buffer, bool cycle)
    {
        auto src = SDL_GPUTransferBufferLocation{.transfer_buffer = ptr_, .offset = 0};
        auto dst = SDL_GPUBufferRegion{.buffer = buffer.ptr(), .offset = 0, .size = size_};
        SDL_UploadToGPUBuffer(copy_pass.ptr(), &src, &dst, cycle);
    }

    void transfer_buffer::upload(const copy_pass &copy_pass, const texture &texture, bool cycle)
    {
        auto src =
            SDL_GPUTextureTransferInfo{.transfer_buffer = ptr_, .offset = 0, .pixels_per_row = 0, .rows_per_layer = 0};
        auto dst = SDL_GPUTextureRegion{.texture = texture.ptr(),
                                        .mip_level = 0,
                                        .layer = 0,
                                        .x = 0,
                                        .y = 0,
                                        .z = 0,
                                        .w = static_cast<uint32_t>(texture.size().w()),
                                        .h = static_cast<uint32_t>(texture.size().h()),
                                        .d = 1};
        SDL_UploadToGPUTexture(copy_pass.ptr(), &src, &dst, cycle);
    }

} // namespace jhoyt::mf::gpu
