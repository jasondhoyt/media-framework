// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include "properties.hpp"

namespace jhoyt::mf
{

    class display_properties final : public properties
    {
    public:
        display_properties(SDL_PropertiesID id);

        std::optional<bool> get_hdr_enabled() const;
    };

} // namespace jhoyt::mf
