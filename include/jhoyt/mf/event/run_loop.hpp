// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <atomic>
#include <memory>

namespace jhoyt::mf
{

    class context;

    namespace evt
    {

        class handler;

        class run_loop final
        {
        public:
            run_loop(std::shared_ptr<context> ctx);

            void run(handler &handler);

            void stop();

        private:
            std::shared_ptr<context> ctx_;
            std::atomic_bool stop_flag_;
        };

    } // namespace evt

} // namespace jhoyt::mf
