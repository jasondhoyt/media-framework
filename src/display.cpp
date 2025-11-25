// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/media-framework/display.hpp"

namespace jhoyt::mf
{

    display display::get_primary()
    {
        const auto id = SDL_GetPrimaryDisplay();
        if (id == 0)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return display{id};
    }

    std::vector<display> display::get_displays()
    {
        auto displays = std::vector<display>{};
        auto count = 0;
        const auto entries = SDL_GetDisplays(&count);
        if (!entries)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        for (auto i = 0; i < count; ++i)
        {
            displays.push_back(display{entries[i]});
        }

        return displays;
    }

    display::display(const SDL_DisplayID id) : id_(id)
    {
    }

    rect display::get_bounds() const
    {
        assert(id_ > 0);

        auto r = SDL_Rect{0};
        if (!SDL_GetDisplayBounds(id_, &r))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {r};
    }

    float display::get_content_scale() const
    {
        assert(id_ > 0);

        if (const auto result = SDL_GetDisplayContentScale(id_); result != 0.0f)
        {
            return result;
        }

        throw std::runtime_error{SDL_GetError()};
    }

    std::string display::get_name() const
    {
        assert(id_ > 0);

        if (const auto result = SDL_GetDisplayName(id_); result)
        {
            return result;
        }

        throw std::runtime_error{SDL_GetError()};
    }

    display_properties display::get_properties() const
    {
        assert(id_ > 0);

        if (const auto id = SDL_GetDisplayProperties(id_); id != 0)
        {
            return {id};
        }

        throw std::runtime_error{SDL_GetError()};
    }

    rect display::get_usable_bounds() const
    {
        assert(id_ > 0);

        auto r = SDL_Rect{0};
        if (!SDL_GetDisplayUsableBounds(id_, &r))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {r};
    }

    display_orientation display::get_current_orientation() const
    {
        assert(id_ > 0);
        return static_cast<display_orientation>(SDL_GetCurrentDisplayOrientation(id_));
    }

    display_orientation display::get_natural_orientation() const
    {
        assert(id_ > 0);
        return static_cast<display_orientation>(SDL_GetNaturalDisplayOrientation(id_));
    }

    const SDL_DisplayMode* display::get_current_mode() const
    {
        assert(id_ > 0);

        if (const auto result = SDL_GetCurrentDisplayMode(id_); result)
        {
            return result;
        }

        throw std::runtime_error{SDL_GetError()};
    }

    const SDL_DisplayMode* display::get_desktop_mode() const
    {
        assert(id_ > 0);

        if (const auto result = SDL_GetDesktopDisplayMode(id_); result)
        {
            return result;
        }

        throw std::runtime_error{SDL_GetError()};
    }

    std::vector<const SDL_DisplayMode*> display::get_fullscreen_modes() const
    {
        assert(id_ > 0);

        auto display_modes = std::vector<const SDL_DisplayMode*>{};
        auto count = 0;
        const auto modes = SDL_GetFullscreenDisplayModes(id_, &count);
        if (!modes)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        for (auto i = 0; i < count; ++i)
        {
            display_modes.emplace_back(modes[i]);
        }

        return display_modes;
    }

    const SDL_DisplayMode*
    display::get_closest_fullscreen_mode(int w, int h, float refresh_rate, bool include_high_density_modes) const
    {
        assert(id_ > 0);

        static auto mode = SDL_DisplayMode{};
        if (!SDL_GetClosestFullscreenDisplayMode(id_, w, h, refresh_rate, include_high_density_modes, &mode))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return &mode;
    }

} // namespace jhoyt::mf