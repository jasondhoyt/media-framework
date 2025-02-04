// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <jhoyt/mf/mf.hpp>

using namespace jhoyt::mf;

namespace
{

    class app_handler : public evt::handler
    {
    public:
        app_handler(evt::run_loop &run_loop) : run_loop_(run_loop)
        {
        }

        void on_quit() override
        {
            run_loop_.stop();
        }

    private:
        evt::run_loop &run_loop_;
    };

} // namespace

int main()
{
    auto ctx = context::create();
    auto win = window::create(ctx, "Basic Window", {1280, 720});

    auto run_loop = evt::run_loop{ctx};
    auto handler = app_handler{run_loop};

    run_loop.run(handler);

    return 0;
}
