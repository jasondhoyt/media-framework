// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/shader.hpp"

#include "jhoyt/mf/gpu/device.hpp"

namespace jhoyt::mf::gpu
{

    shader_ptr shader::create(device_ptr device,
                              const std::span<const uint8_t> &data,
                              const std::string &entrypoint,
                              shader_format format,
                              shader_stage stage,
                              const shader_options &opts)
    {
        assert(device);

        auto info = SDL_GPUShaderCreateInfo{.code_size = data.size(),
                                            .code = data.data(),
                                            .entrypoint = entrypoint.c_str(),
                                            .format = static_cast<SDL_GPUShaderFormat>(format),
                                            .stage = static_cast<SDL_GPUShaderStage>(stage),
                                            .num_samplers = opts.num_samplers(),
                                            .num_storage_textures = opts.num_storage_textures(),
                                            .num_storage_buffers = opts.num_storage_buffers(),
                                            .num_uniform_buffers = opts.num_uniform_buffers()};
        auto ptr = SDL_CreateGPUShader(device->ptr(), &info);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return shader_ptr{new shader(std::move(device), ptr)};
    }

    shader::shader(std::shared_ptr<device> device, SDL_GPUShader *ptr) : device_(std::move(device)), ptr_(ptr)
    {
    }

    shader::~shader()
    {
        SDL_ReleaseGPUShader(device_->ptr(), ptr_);
    }

} // namespace jhoyt::mf::gpu
