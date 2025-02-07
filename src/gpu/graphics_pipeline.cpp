// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/graphics_pipeline.hpp"

#include "jhoyt/mf/gpu/device.hpp"
#include "jhoyt/mf/gpu/graphics_pipeline_descriptor.hpp"

namespace jhoyt::mf::gpu
{

    graphics_pipeline_ptr graphics_pipeline::create(device_ptr device, const graphics_pipeline_descriptor &desc)
    {
        assert(device);

        auto info = SDL_GPUGraphicsPipelineCreateInfo{0};
        desc.fill_create_info(info);

        auto ptr = SDL_CreateGPUGraphicsPipeline(device->ptr(), &info);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return graphics_pipeline_ptr{new graphics_pipeline(std::move(device), ptr)};
    }

    graphics_pipeline::graphics_pipeline(std::shared_ptr<device> device, SDL_GPUGraphicsPipeline *ptr)
        : device_(std::move(device)), ptr_(ptr)
    {
    }

    graphics_pipeline::~graphics_pipeline()
    {
        SDL_ReleaseGPUGraphicsPipeline(device_->ptr(), ptr_);
    }

} // namespace jhoyt::mf::gpu
