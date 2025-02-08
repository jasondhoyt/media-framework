// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>

#include <SDL3/SDL_gpu.h>

#include "../fwd.hpp"
#include "filter.hpp"
#include "sampler_address_mode.hpp"
#include "sampler_mipmap_mode.hpp"
#include "sampler_options.hpp"

namespace jhoyt::mf::gpu
{

    class device;

    class sampler final
    {
    public:
        static sampler_ptr create(device_ptr device,
                                  filter min_filter,
                                  filter mag_filter,
                                  sampler_mipmap_mode mipmap_mode,
                                  sampler_address_mode address_mode_u,
                                  sampler_address_mode address_mode_v,
                                  sampler_address_mode address_mode_w,
                                  const sampler_options &opts = {});

        ~sampler();

        sampler(const sampler &) = delete;
        sampler &operator=(const sampler &) = delete;

        sampler(sampler &&) = delete;
        sampler &operator=(sampler &&) = delete;

        auto ptr() const
        {
            return ptr_;
        }

    private:
        device_ptr device_;
        SDL_GPUSampler *ptr_;

        sampler(device_ptr device, SDL_GPUSampler *ptr);
    };

} // namespace jhoyt::mf::gpu
