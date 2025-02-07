// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <vector>

#include <SDL3/SDL_gpu.h>

#include "../fwd.hpp"
#include "blend_state.hpp"
#include "primitive_type.hpp"
#include "texture_format.hpp"
#include "vertex_element_format.hpp"
#include "vertex_input_rate.hpp"

namespace jhoyt::mf::gpu
{

    class graphics_pipeline_descriptor final
    {
    public:
        graphics_pipeline_descriptor(shader_ptr vertex_shader,
                                     shader_ptr fragment_shader,
                                     primitive_type primitive_type = primitive_type::triangle_list);

        void add_color_target_description(texture_format format, const blend_state &blend_state = {});

        void add_vertex_buffer_description(uint32_t slot,
                                           uint32_t pitch,
                                           vertex_input_rate input_rate,
                                           uint32_t instance_step_rate = 0);
        void
        add_vertex_attribute(uint32_t location, uint32_t buffer_slot, vertex_element_format format, uint32_t offset);

        void fill_create_info(SDL_GPUGraphicsPipelineCreateInfo &info) const;

    private:
        shader_ptr vertex_shader_;
        shader_ptr fragment_shader_;
        primitive_type primitive_type_;
        std::vector<SDL_GPUColorTargetDescription> color_target_descriptions_;
        std::vector<SDL_GPUVertexBufferDescription> vertex_buffer_descriptions_;
        std::vector<SDL_GPUVertexAttribute> vertex_attributes_;
    };

} // namespace jhoyt::mf::gpu
