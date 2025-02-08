// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/sampler.hpp"

#include "jhoyt/mf/gpu/device.hpp"

namespace jhoyt::mf::gpu
{

    sampler_ptr sampler::create(device_ptr device,
                                filter min_filter,
                                filter mag_filter,
                                sampler_mipmap_mode mipmap_mode,
                                sampler_address_mode address_mode_u,
                                sampler_address_mode address_mode_v,
                                sampler_address_mode address_mode_w,
                                const sampler_options &opts)
    {
        assert(device);

        auto info = SDL_GPUSamplerCreateInfo{.min_filter = static_cast<SDL_GPUFilter>(min_filter),
                                             .mag_filter = static_cast<SDL_GPUFilter>(mag_filter),
                                             .mipmap_mode = static_cast<SDL_GPUSamplerMipmapMode>(mipmap_mode),
                                             .address_mode_u = static_cast<SDL_GPUSamplerAddressMode>(address_mode_u),
                                             .address_mode_v = static_cast<SDL_GPUSamplerAddressMode>(address_mode_v),
                                             .address_mode_w = static_cast<SDL_GPUSamplerAddressMode>(address_mode_w),
                                             .mip_lod_bias = opts.mip_lod_bias(),
                                             .max_anisotropy = opts.max_anistropy(),
                                             .compare_op = static_cast<SDL_GPUCompareOp>(opts.compare_op()),
                                             .min_lod = opts.min_lod(),
                                             .max_lod = opts.max_lod(),
                                             .enable_anisotropy = opts.enable_anistropy(),
                                             .enable_compare = opts.enable_compare()};
        auto ptr = SDL_CreateGPUSampler(device->ptr(), &info);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return sampler_ptr{new sampler(std::move(device), ptr)};
    }

    sampler::sampler(device_ptr device, SDL_GPUSampler *ptr) : device_(std::move(device)), ptr_(ptr)
    {
    }

    sampler::~sampler()
    {
        SDL_ReleaseGPUSampler(device_->ptr(), ptr_);
    }

} // namespace jhoyt::mf::gpu
