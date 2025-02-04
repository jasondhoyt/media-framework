// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/window.hpp"

namespace jhoyt::mf
{

    std::shared_ptr<window> window::create(std::shared_ptr<context> ctx, const std::string &title, const size &size)
    {
        assert(ctx);
        assert(size);

        auto ptr = SDL_CreateWindow(title.c_str(), size.w(), size.h(), 0);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return std::shared_ptr<window>(new window(std::move(ctx), ptr));
    }

    window::window(std::shared_ptr<context> ctx, SDL_Window *ptr) : ctx_(std::move(ctx)), ptr_(ptr)
    {
    }

    window::~window()
    {
        SDL_DestroyWindow(ptr_);
    }

} // namespace jhoyt::mf
