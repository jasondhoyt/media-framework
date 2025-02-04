// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <chrono>

#include <SDL3/SDL_events.h>

#include "jhoyt/mf/event/run_loop.hpp"

#include "jhoyt/mf/event/handler.hpp"

namespace
{
    constexpr auto k_nanoseconds_per_second = 1000000000.0;
}

namespace jhoyt::mf::evt
{

    run_loop::run_loop(std::shared_ptr<context> ctx) : ctx_(std::move(ctx))
    {
        assert(ctx_);
    }

    void run_loop::run(handler &handler)
    {
        stop_flag_ = false;

        auto evt = SDL_Event{};
        auto start = std::chrono::steady_clock::now();
        while (!stop_flag_)
        {
            while (SDL_PollEvent(&evt))
            {
                switch (evt.type)
                {
                case SDL_EVENT_QUIT:
                    handler.on_quit();
                    break;
                default:
                    break;
                }
            }

            auto now = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
            handler.on_frame(static_cast<double>(elapsed_ns) / k_nanoseconds_per_second);
        }
    }

    void run_loop::stop()
    {
        stop_flag_ = true;
    }

} // namespace jhoyt::mf::evt
