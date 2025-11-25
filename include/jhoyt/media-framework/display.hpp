// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <vector>

#include <SDL3/SDL_video.h>

#include "display_properties.hpp"
#include "rect.hpp"

namespace jhoyt::mf
{

    enum class display_orientation
    {
        unknown = SDL_ORIENTATION_UNKNOWN,
        landscape = SDL_ORIENTATION_LANDSCAPE,
        landscape_flipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
        portrait = SDL_ORIENTATION_PORTRAIT,
        portrait_flipped = SDL_ORIENTATION_PORTRAIT_FLIPPED
    };

    class display final
    {
    public:
        static display get_primary();
        static std::vector<display> get_displays();

        display() = default;

        [[nodiscard]] rect get_bounds() const;
        [[nodiscard]] float get_content_scale() const;
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] display_properties get_properties() const;
        [[nodiscard]] rect get_usable_bounds() const;
        [[nodiscard]] display_orientation get_current_orientation() const;
        [[nodiscard]] display_orientation get_natural_orientation() const;
        [[nodiscard]] const SDL_DisplayMode* get_current_mode() const;
        [[nodiscard]] const SDL_DisplayMode* get_desktop_mode() const;
        [[nodiscard]] std::vector<const SDL_DisplayMode*> get_fullscreen_modes() const;
        [[nodiscard]] const SDL_DisplayMode*
        get_closest_fullscreen_mode(int w, int h, float refresh_rate, bool include_high_density_modes) const;

    private:
        SDL_DisplayID id_ = 0;

        explicit display(SDL_DisplayID id);
    };

} // namespace jhoyt::mf