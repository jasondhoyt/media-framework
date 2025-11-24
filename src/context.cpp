// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <mutex>
#include <stdexcept>

#include "jhoyt/media-framework/context.hpp"

namespace
{

    auto g_init_mutex = std::mutex{};
    auto g_init_count = 0;

    void inc_init_count()
    {
        auto guard = std::lock_guard{g_init_mutex};
        ++g_init_count;
    }

    void dec_init_count()
    {
        auto guard = std::lock_guard{g_init_mutex};
        --g_init_count;
        assert(g_init_count >= 0);

        if (g_init_count == 0)
        {
            SDL_Quit();
        }
    }

} // namespace

namespace jhoyt::mf
{

    context::context()
    {
        inc_init_count();
    }

    context::context(const subsystem_flags subsystems) : init_flags_(subsystems)
    {
        if (init_flags_.value() > 0)
        {
            if (!SDL_InitSubSystem(init_flags_.value()))
            {
                throw std::runtime_error{SDL_GetError()};
            }
        }

        inc_init_count();
    }

    context::~context()
    {
        quit();
        dec_init_count();
    }

    context::context(context&& other) noexcept : init_flags_(other.init_flags_)
    {
        other.init_flags_ = {};
    }

    context& context::operator=(context&& other) noexcept
    {
        if (this != &other)
        {
            quit();
            std::swap(init_flags_, other.init_flags_);
        }

        return *this;
    }

    void context::quit()
    {
        if (init_flags_.value() > 0)
        {
            SDL_QuitSubSystem(init_flags_.value());
            init_flags_ = {};
        }
    }

} // namespace jhoyt::mf