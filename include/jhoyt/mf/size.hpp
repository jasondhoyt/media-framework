// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

namespace jhoyt::mf
{

    class size final
    {
    public:
        size() = default;

        size(int w, int h) : w_(w), h_(h)
        {
        }

        operator bool() const
        {
            return w_ > 0 && h_ > 0;
        }

        auto w() const
        {
            return w_;
        }

        auto h() const
        {
            return h_;
        }

    private:
        int w_ = 0;
        int h_ = 0;
    };

} // namespace jhoyt::mf
