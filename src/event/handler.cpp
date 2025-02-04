// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <chrono>
#include <thread>

#include "jhoyt/mf/event/handler.hpp"

namespace jhoyt::mf::evt
{

    handler::~handler() = default;

    void handler::on_frame(double dt)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{10});
    }

    void handler::on_quit()
    {
    }

} // namespace jhoyt::mf::evt
