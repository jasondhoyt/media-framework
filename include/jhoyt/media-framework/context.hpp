// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include "subsystem.hpp"

namespace jhoyt::mf
{

    class context final
    {
    public:
        context();
        explicit context(subsystem_flags subsystems);
        ~context();

        context(const context&) = delete;
        context& operator=(const context&) = delete;

        context(context&& other) noexcept;
        context& operator=(context&& other) noexcept;

    private:
        subsystem_flags init_flags_ = {};

        void quit();
    };

} // namespace jhoyt::mf
