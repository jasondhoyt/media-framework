// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <cstdint>

namespace jhoyt::mf::gpu
{

    class shader_options final
    {
    public:
        auto num_samplers() const
        {
            return num_samplers_;
        }

        auto num_storage_textures() const
        {
            return num_storage_textures_;
        }

        auto num_storage_buffers() const
        {
            return num_storage_buffers_;
        }

        auto num_uniform_buffers() const
        {
            return num_uniform_buffers_;
        }

        shader_options &num_samplers(uint32_t value)
        {
            num_samplers_ = value;
            return *this;
        }

        shader_options &num_storage_textures(uint32_t value)
        {
            num_storage_textures_ = value;
            return *this;
        }

        shader_options &num_storage_buffers(uint32_t value)
        {
            num_storage_buffers_ = value;
            return *this;
        }

        shader_options &num_uniform_buffers(uint32_t value)
        {
            num_uniform_buffers_ = value;
            return *this;
        }

    private:
        uint32_t num_samplers_ = 0;
        uint32_t num_storage_textures_ = 0;
        uint32_t num_storage_buffers_ = 0;
        uint32_t num_uniform_buffers_ = 0;
    };

} // namespace jhoyt::mf::gpu
