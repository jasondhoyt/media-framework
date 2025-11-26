// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include "properties.hpp"

namespace jhoyt::mf
{

    class window_properties final : public properties
    {
    public:
        explicit window_properties(SDL_PropertiesID id);

        std::optional<bool> get_hdr_enabled() const;
        std::optional<float> get_sdr_white_level() const;
        std::optional<float> get_hdr_headroom_float() const;
    };

} // namespace jhoyt::mf
