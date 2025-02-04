// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

namespace jhoyt::mf::evt
{

    class handler
    {
    public:
        virtual ~handler();

        virtual void on_frame(double dt);

        virtual void on_quit();
    };

} // namespace jhoyt::mf::evt
