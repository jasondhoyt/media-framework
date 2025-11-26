// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "jhoyt/media-framework/window_properties.hpp"

#include <SDL3/SDL_video.h>

namespace jhoyt::mf
{

    window_properties::window_properties(SDL_PropertiesID id) : properties(id, false)
    {
    }

    std::optional<bool> window_properties::get_hdr_enabled() const
    {
        auto value = get_property(SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN);
        if (get_type(value) == property_type::boolean)
        {
            return *std::get_if<bool>(&value);
        }

        return {};
    }

    std::optional<float> window_properties::get_sdr_white_level() const
    {
        auto value = get_property(SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT);
        if (get_type(value) == property_type::real)
        {
            return *std::get_if<float>(&value);
        }

        return {};
    }

    std::optional<float> window_properties::get_hdr_headroom_float() const
    {
        auto value = get_property(SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT);
        if (get_type(value) == property_type::real)
        {
            return *std::get_if<float>(&value);
        }

        return {};
    }

} // namespace jhoyt::mf