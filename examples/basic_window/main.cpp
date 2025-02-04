// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <jhoyt/mf/mf.hpp>

using namespace jhoyt::mf;

namespace
{

    class app_handler : public evt::handler
    {
    public:
        app_handler(std::shared_ptr<gpu::device> device, window &window, evt::run_loop &run_loop)
            : device_(std::move(device)), window_(window), run_loop_(run_loop)
        {
        }

        void on_frame(double dt) override
        {
            auto cmd_buf = gpu::command_buffer{device_};
            if (auto window_texture = cmd_buf.wait_and_acquire_swapchain_texture(window_); window_texture)
            {
                gpu::render_pass{cmd_buf, window_texture, {0.3f, 0.4f, 0.5f}}.end();
            }

            cmd_buf.submit();
        }

        void on_quit() override
        {
            run_loop_.stop();
        }

    private:
        std::shared_ptr<gpu::device> device_;
        window &window_;
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
    auto handler = app_handler{gpu, *win, run_loop};

    run_loop.run(handler);

    return 0;
}
