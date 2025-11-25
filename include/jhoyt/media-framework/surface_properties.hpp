// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <optional>

#include "properties.hpp"

namespace jhoyt::mf
{

    class surface_properties final : public properties
    {
    public:
        surface_properties(SDL_PropertiesID id);

        std::optional<float> get_sdr_white_point() const;
        std::optional<float> get_hdr_headroom() const;
        std::optional<std::string> get_tonemap_operator() const;
        std::optional<int> get_hotspot_x() const;
        std::optional<int> get_hotspot_y() const;

        void set_sdr_white_point(std::optional<float> value);
        void set_hdr_headroom(std::optional<float> value);
        void set_tonemap_operator(std::optional<std::string> value);
        void set_hotspot_x(std::optional<int> value);
        void set_hotspot_y(std::optional<int> value);
    };

} // namespace jhoyt::mf