// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>
#include <string>

#include <SDL3/SDL_video.h>

#include "size.hpp"

namespace jhoyt::mf
{

    class context;

    class window final
    {
    public:
        static std::shared_ptr<window> create(std::shared_ptr<context> ctx, const std::string &title, const size &size);

        ~window();

        window(const window &) = delete;
        window &operator=(const window &) = delete;

        window(window &&) = delete;
        window &operator=(const window &&) = delete;

        auto ptr() const
        {
            return ptr_;
        }

    private:
        std::shared_ptr<context> ctx_;
        SDL_Window *ptr_;

        window(std::shared_ptr<context> ctx, SDL_Window *ptr);
    };

} // namespace jhoyt::mf
