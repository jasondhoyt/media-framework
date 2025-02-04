// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <stdexcept>

#include <SDL3/SDL_init.h>

#include "jhoyt/mf/context.hpp"

namespace
{
    auto g_instance = static_cast<jhoyt::mf::context *>(nullptr);
}

namespace jhoyt::mf
{

    std::shared_ptr<context> context::create()
    {
        if (g_instance)
        {
            throw std::runtime_error{"library context already created"};
        }

        return std::shared_ptr<context>(new context());
    }

    context::context()
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        g_instance = this;
    }

    context::~context()
    {
        SDL_Quit();

        g_instance = nullptr;
    }

} // namespace jhoyt::mf
