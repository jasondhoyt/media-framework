// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <jhoyt/mf/mf.hpp>

using namespace jhoyt::mf;

namespace
{

    class app_handler : public evt::handler
    {
    public:
        app_handler(gpu::device_ptr device, window_ptr window, evt::run_loop &run_loop)
            : device_(std::move(device)), window_(std::move(window)), run_loop_(run_loop)
        {
        }

        void on_frame(double dt) override
        {
            device_->acquire_command_buffer([this](gpu::command_buffer &cmd_buf) {
                cmd_buf.enqueue_render_pass(
                    *window_, {0.3f, 0.4f, 0.5f, 1.0f}, [this](gpu::render_pass &render_pass, const size &size) {});
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
    };

} // namespace

int main()
{
    auto ctx = context::create();
    auto win = window::create(ctx, "Basic Window", {1280, 720});

    auto gpu = gpu::device::create(ctx, gpu::shader_format_flags{gpu::shader_format::dxil});
    gpu->claim_window(win);

    auto run_loop = evt::run_loop{ctx};
    auto handler = app_handler{gpu, win, run_loop};

    run_loop.run(handler);

    return 0;
}
