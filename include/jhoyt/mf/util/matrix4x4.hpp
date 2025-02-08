// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <array>

#include "../size.hpp"

namespace jhoyt::mf::util
{

    using matrix4x4 = std::array<float, 16>;

    matrix4x4 create_2d_orthographic_matrix(const size &size);

} // namespace jhoyt::mf::util
