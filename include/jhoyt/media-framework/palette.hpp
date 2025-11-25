// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <span>

#include <SDL3/SDL_pixels.h>

#include "color.hpp"

namespace jhoyt::mf
{

    class palette final
    {
    public:
        palette() = default;
        explicit palette(int num_colors);
        palette(SDL_Palette* ptr, bool auto_destroy);
        ~palette();

        palette(const palette&) = delete;
        palette& operator=(const palette&) = delete;

        palette(palette&& other) noexcept;
        palette& operator=(palette&& other) noexcept;

        void destroy();

        [[nodiscard]] std::span<const color> get_colors() const;
        std::span<color> get_colors();

        [[nodiscard]] color get_color(int ix) const;

        void set_color(int ix, const color& color);

        [[nodiscard]] auto get_ptr() const
        {
            return ptr_;
        }

    private:
        SDL_Palette* ptr_ = nullptr;
        bool auto_destroy_ = true;
    };

} // namespace jhoyt::mf