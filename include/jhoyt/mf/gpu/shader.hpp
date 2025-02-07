// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>
#include <span>
#include <string>

#include <SDL3/SDL_gpu.h>

#include "../fwd.hpp"
#include "shader_format.hpp"
#include "shader_options.hpp"
#include "shader_stage.hpp"

namespace jhoyt::mf::gpu
{

    class device;

    class shader final
    {
    public:
        static shader_ptr create(std::shared_ptr<device> device,
                                 const std::span<const uint8_t> &data,
                                 const std::string &entrypoint,
                                 shader_format format,
                                 shader_stage stage,
                                 const shader_options &opts = {});

        ~shader();

        shader(const shader &) = delete;
        shader &operator=(const shader &) = delete;

        shader(shader &&) = delete;
        shader &operator=(shader &&) = delete;

        auto ptr() const
        {
            return ptr_;
        }

    private:
        std::shared_ptr<device> device_;
        SDL_GPUShader *ptr_;

        shader(std::shared_ptr<device> device, SDL_GPUShader *ptr);
    };

} // namespace jhoyt::mf::gpu
