// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>

#include <SDL3/SDL_gpu.h>

#include "../fwd.hpp"

namespace jhoyt::mf::gpu
{

    class device;
    class graphics_pipeline_descriptor;
    class shader;

    class graphics_pipeline final
    {
    public:
        static graphics_pipeline_ptr create(device_ptr device, const graphics_pipeline_descriptor &desc);

        ~graphics_pipeline();

        graphics_pipeline(const graphics_pipeline &) = delete;
        graphics_pipeline &operator=(const graphics_pipeline &) = delete;

        graphics_pipeline(graphics_pipeline &&) = delete;
        graphics_pipeline &operator=(graphics_pipeline &&) = delete;

        auto ptr() const
        {
            return ptr_;
        }

    private:
        device_ptr device_;
        SDL_GPUGraphicsPipeline *ptr_;

        graphics_pipeline(std::shared_ptr<device> device, SDL_GPUGraphicsPipeline *ptr);
    };

} // namespace jhoyt::mf::gpu
