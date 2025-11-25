// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>

#include "jhoyt/media-framework/display_properties.hpp"

#include <SDL3/SDL_video.h>

namespace jhoyt::mf
{

    display_properties::display_properties(const SDL_PropertiesID id) : properties(id, false)
    {
        assert(id > 0);
    }

    std::optional<bool> display_properties::get_hdr_enabled() const
    {
        auto value = get_property(SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN);
        if (get_type(value) != property_type::boolean)
        {
            return {};
        }

        return *std::get_if<bool>(&value);
    }

} // namespace jhoyt::mf