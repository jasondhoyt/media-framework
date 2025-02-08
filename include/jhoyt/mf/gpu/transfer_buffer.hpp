// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>
#include <span>
#include <vector>

#include <SDL3/SDL_gpu.h>

#include "../fwd.hpp"
#include "transfer_buffer_usage.hpp"

namespace jhoyt::mf
{

    class surface;

    namespace gpu
    {

        class copy_pass;
        class device;
        class texture;

        class transfer_buffer final
        {
        public:
            static transfer_buffer_ptr create(device_ptr device, transfer_buffer_usage usage, uint32_t size);

            ~transfer_buffer();

            transfer_buffer(const transfer_buffer &) = delete;
            transfer_buffer &operator=(const transfer_buffer &) = delete;

            transfer_buffer(transfer_buffer &&) = delete;
            transfer_buffer &operator=(transfer_buffer &&) = delete;

            void copy_data(const std::span<const uint8_t> &data, bool cycle = true);
            void copy_data(const surface &surface, bool cycle = true);

            template <class T> void copy_data(const std::vector<T> &data, bool cycle = true)
            {
                copy_data(
                    std::span<const uint8_t>{reinterpret_cast<const uint8_t *>(data.data()), sizeof(T) * data.size()},
                    cycle);
            }

            void upload(const copy_pass &copy_pass, const buffer &buffer, bool cycle = true);
            void upload(const copy_pass &copy_pass, const texture &texture, bool cycle = true);

            auto size() const
            {
                return size_;
            }

            auto ptr() const
            {
                return ptr_;
            }

        private:
            device_ptr device_;
            SDL_GPUTransferBuffer *ptr_;
            uint32_t size_;

            transfer_buffer(device_ptr device, SDL_GPUTransferBuffer *ptr, uint32_t size);
        };

    } // namespace gpu

} // namespace jhoyt::mf
