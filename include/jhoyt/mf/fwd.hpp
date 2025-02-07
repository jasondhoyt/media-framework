// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>

namespace jhoyt::mf
{

    class context;
    using context_ptr = std::shared_ptr<context>;

    class window;
    using window_ptr = std::shared_ptr<window>;

    namespace gpu
    {

        class device;
        using device_ptr = std::shared_ptr<device>;

        class shader;
        using shader_ptr = std::shared_ptr<shader>;

        class sampler;
        using sampler_ptr = std::shared_ptr<sampler>;

        class texture;
        using texture_ptr = std::shared_ptr<texture>;

        class buffer;
        using buffer_ptr = std::shared_ptr<buffer>;

        class transfer_buffer;
        using transfer_buffer_ptr = std::shared_ptr<transfer_buffer>;

        class graphics_pipeline;
        using graphics_pipeline_ptr = std::shared_ptr<graphics_pipeline>;

    } // namespace gpu

} // namespace jhoyt::mf
