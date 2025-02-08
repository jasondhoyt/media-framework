// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <jhoyt/mf/mf.hpp>

#include "image.png.hpp"
#include "position_tex_coord_color_vert_dxil.hpp"
#include "tex_coord_color_frag_dxil.hpp"

using namespace jhoyt::mf;

namespace
{

    struct vertex
    {
        float x, y;
        float u, v;
        float r, g, b, a;
    };

    class app_handler : public evt::handler
    {
    public:
        app_handler(gpu::device_ptr device, window_ptr window, evt::run_loop &run_loop)
            : device_(std::move(device)), window_(std::move(window)), run_loop_(run_loop)
        {
            auto vertex_shader = gpu::shader::create(
                device_,
                {g_position_tex_coord_color_vert_dxil_data, sizeof(g_position_tex_coord_color_vert_dxil_data)},
                "main",
                gpu::shader_format::dxil,
                gpu::shader_stage::vertex);

            auto fragment_shader =
                gpu::shader::create(device_,
                                    {g_tex_coord_color_frag_dxil_data, sizeof(g_tex_coord_color_frag_dxil_data)},
                                    "main",
                                    gpu::shader_format::dxil,
                                    gpu::shader_stage::fragment,
                                    gpu::shader_options{}.num_samplers(1));

            auto desc = gpu::graphics_pipeline_descriptor{vertex_shader, fragment_shader};
            desc.add_color_target_description(device_->swapchain_texture_format(*window_),
                                              gpu::blend_state::basic_blend_state());
            desc.add_vertex_buffer_description(0, sizeof(vertex), gpu::vertex_input_rate::vertex);
            desc.add_vertex_attribute(0, 0, gpu::vertex_element_format::float2, 0);
            desc.add_vertex_attribute(1, 0, gpu::vertex_element_format::float2, sizeof(float) * 2);
            desc.add_vertex_attribute(2, 0, gpu::vertex_element_format::float4, sizeof(float) * 4);
            gfx_pipeline_ = gpu::graphics_pipeline::create(device_, desc);

            auto image = surface{{g_image_data, sizeof(g_image_data)}};
            image.convert_to_format(pixel_format::abgr8888);

            auto transfer_buffer = gpu::transfer_buffer::create(
                device_, gpu::transfer_buffer_usage::upload, image.size().w() * image.size().h() * 4);

            transfer_buffer->copy_data(image);

            texture_ = gpu::texture::create(device_,
                                            gpu::texture_type::d2,
                                            gpu::texture_format::r8g8b8a8_unorm,
                                            gpu::texture_usage_flags{gpu::texture_usage::sampler},
                                            image.size());

            sampler_ = gpu::sampler::create(device_,
                                            gpu::filter::nearest,
                                            gpu::filter::nearest,
                                            gpu::sampler_mipmap_mode::nearest,
                                            gpu::sampler_address_mode::clamp_to_edge,
                                            gpu::sampler_address_mode::clamp_to_edge,
                                            gpu::sampler_address_mode::clamp_to_edge);

            device_->acquire_command_buffer([this, &transfer_buffer](gpu::command_buffer &cmd_buf) {
                cmd_buf.enqueue_copy_pass([this, &transfer_buffer](gpu::copy_pass &copy_pass) {
                    transfer_buffer->upload(copy_pass, *texture_);
                });
            });

            vertices_.emplace_back(-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.25f);
            vertices_.emplace_back(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f);
            vertices_.emplace_back(-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.75f);
            vertices_.emplace_back(1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

            indices_.emplace_back(0);
            indices_.emplace_back(1);
            indices_.emplace_back(2);
            indices_.emplace_back(2);
            indices_.emplace_back(1);
            indices_.emplace_back(3);

            vertex_buffer_ = gpu::buffer::create(device_, gpu::buffer_usage::vertex, sizeof(vertex) * vertices_.size());
            vertex_transfer_buffer_ = gpu::transfer_buffer::create(
                device_, gpu::transfer_buffer_usage::upload, sizeof(vertex) * vertices_.size());

            index_buffer_ = gpu::buffer::create(device_, gpu::buffer_usage::index, sizeof(uint32_t) * indices_.size());
            index_transfer_buffer_ = gpu::transfer_buffer::create(
                device_, gpu::transfer_buffer_usage::upload, sizeof(uint32_t) * indices_.size());
        }

        void on_frame(double dt) override
        {
            vertex_transfer_buffer_->copy_data(vertices_);
            index_transfer_buffer_->copy_data(indices_);

            device_->acquire_command_buffer([this](gpu::command_buffer &cmd_buf) {
                cmd_buf.enqueue_copy_pass([this](gpu::copy_pass &copy_pass) {
                    vertex_transfer_buffer_->upload(copy_pass, *vertex_buffer_);
                    index_transfer_buffer_->upload(copy_pass, *index_buffer_);
                });

                cmd_buf.enqueue_render_pass(*window_,
                                            {0.3f, 0.4f, 0.5f, 1.0f},
                                            *gfx_pipeline_,
                                            [this](gpu::render_pass &render_pass, const size &size) {
                                                render_pass.bind_vertex_buffer(0, *vertex_buffer_);
                                                render_pass.bind_index_buffer(*index_buffer_,
                                                                              gpu::index_element_size::bits_32);
                                                render_pass.bind_fragment_sampler(0, *texture_, *sampler_);
                                                render_pass.draw_indexed_primitives(6);
                                            });
            });
        }

        void on_quit() override
        {
            run_loop_.stop();
        }

    private:
        gpu::device_ptr device_;
        window_ptr window_;
        evt::run_loop &run_loop_;

        gpu::graphics_pipeline_ptr gfx_pipeline_;

        gpu::texture_ptr texture_;
        gpu::sampler_ptr sampler_;

        std::vector<vertex> vertices_;
        std::vector<uint32_t> indices_;

        gpu::buffer_ptr vertex_buffer_;
        gpu::transfer_buffer_ptr vertex_transfer_buffer_;

        gpu::buffer_ptr index_buffer_;
        gpu::transfer_buffer_ptr index_transfer_buffer_;
    };

} // namespace

int main()
{
    auto ctx = context::create();
    auto win = window::create(ctx, "Basic Textured Quad", {1280, 720});

    auto gpu = gpu::device::create(ctx, gpu::shader_format_flags{gpu::shader_format::dxil});
    gpu->claim_window(win);

    auto run_loop = evt::run_loop{ctx};
    auto handler = app_handler{gpu, win, run_loop};

    run_loop.run(handler);

    return 0;
}
