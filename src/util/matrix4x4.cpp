// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "jhoyt/mf/util/matrix4x4.hpp"

namespace jhoyt::mf::util
{

    matrix4x4 create_2d_orthographic_matrix(const size &size)
    {
        auto left = 0.0f;
        auto right = static_cast<float>(size.w());
        auto bottom = static_cast<float>(size.h());
        auto top = 0.0f;
        auto near = 0.0f;
        auto far = -1.0f;

        return matrix4x4{{2.0f / (right - left),
                          0.0f,
                          0.0f,
                          0.0f,
                          0.0f,
                          2.0f / (top - bottom),
                          0.0f,
                          0.0f,
                          0.0f,
                          0.0f,
                          1.0f / (near - far),
                          0.0f,
                          (left + right) / (left - right),
                          (top + bottom) / (bottom - top),
                          near / (near - far),
                          1.0f}};
    }

} // namespace jhoyt::mf::util
