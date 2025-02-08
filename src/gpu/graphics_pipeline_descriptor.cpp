// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "jhoyt/mf/gpu/graphics_pipeline_descriptor.hpp"

#include "jhoyt/mf/gpu/shader.hpp"

namespace jhoyt::mf::gpu
{

    graphics_pipeline_descriptor::graphics_pipeline_descriptor(shader_ptr vertex_shader,
                                                               shader_ptr fragment_shader,
                                                               primitive_type primitive_type)
        : vertex_shader_(vertex_shader), fragment_shader_(fragment_shader), primitive_type_(primitive_type)
    {
    }

    void graphics_pipeline_descriptor::add_color_target_description(texture_format format,
                                                                    const blend_state &blend_state)
    {
        auto info = SDL_GPUColorTargetDescription{
            .format = static_cast<SDL_GPUTextureFormat>(format),
            .blend_state = {
                .src_color_blendfactor = static_cast<SDL_GPUBlendFactor>(blend_state.src_color_blend_factor()),
                .dst_color_blendfactor = static_cast<SDL_GPUBlendFactor>(blend_state.dst_color_blend_factor()),
                .color_blend_op = static_cast<SDL_GPUBlendOp>(blend_state.color_blend_op()),
                .src_alpha_blendfactor = static_cast<SDL_GPUBlendFactor>(blend_state.src_alpha_blend_factor()),
                .dst_alpha_blendfactor = static_cast<SDL_GPUBlendFactor>(blend_state.dst_alpha_blend_factor()),
                .alpha_blend_op = static_cast<SDL_GPUBlendOp>(blend_state.alpha_blend_op()),
                .color_write_mask = blend_state.color_write_mask().value(),
                .enable_blend = blend_state.enable_blend(),
                .enable_color_write_mask = blend_state.enable_color_write_mask()}};
        color_target_descriptions_.emplace_back(info);
    }

    void graphics_pipeline_descriptor::add_vertex_buffer_description(uint32_t slot,
                                                                     uint32_t pitch,
                                                                     vertex_input_rate input_rate,
                                                                     uint32_t instance_step_rate)
    {
        auto info = SDL_GPUVertexBufferDescription{.slot = slot,
                                                   .pitch = pitch,
                                                   .input_rate = static_cast<SDL_GPUVertexInputRate>(input_rate),
                                                   .instance_step_rate = instance_step_rate};
        vertex_buffer_descriptions_.emplace_back(info);
    }

    void graphics_pipeline_descriptor::add_vertex_attribute(uint32_t location,
                                                            uint32_t buffer_slot,
                                                            vertex_element_format format,
                                                            uint32_t offset)
    {
        auto info = SDL_GPUVertexAttribute{.location = location,
                                           .buffer_slot = buffer_slot,
                                           .format = static_cast<SDL_GPUVertexElementFormat>(format),
                                           .offset = offset};
        vertex_attributes_.emplace_back(info);
    }

    void graphics_pipeline_descriptor::fill_create_info(SDL_GPUGraphicsPipelineCreateInfo &info) const
    {
        info.vertex_shader = vertex_shader_->ptr();
        info.fragment_shader = fragment_shader_->ptr();
        info.primitive_type = static_cast<SDL_GPUPrimitiveType>(primitive_type_);

        info.target_info.num_color_targets = static_cast<uint32_t>(color_target_descriptions_.size());
        info.target_info.color_target_descriptions = color_target_descriptions_.data();

        info.vertex_input_state.num_vertex_buffers = static_cast<uint32_t>(vertex_buffer_descriptions_.size());
        info.vertex_input_state.vertex_buffer_descriptions = vertex_buffer_descriptions_.data();
        info.vertex_input_state.num_vertex_attributes = static_cast<uint32_t>(vertex_attributes_.size());
        info.vertex_input_state.vertex_attributes = vertex_attributes_.data();
    }

} // namespace jhoyt::mf::gpu
