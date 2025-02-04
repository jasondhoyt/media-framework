// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <cstdint>

namespace jhoyt::mf
{

    template <class T, class Storage> class bit_flags final
    {
    public:
        bit_flags() = default;

        bit_flags(Storage value) : value_(value)
        {
        }

        bit_flags(T value) : value_(static_cast<Storage>(value))
        {
        }

        bit_flags &add(T value)
        {
            value_ |= static_cast<Storage>(value);
            return *this;
        }

        auto contains(T value) const
        {
            return (value_ & static_cast<Storage>(value)) != 0;
        }

        auto value() const
        {
            return value_;
        }

    private:
        Storage value_ = 0;
    };

} // namespace jhoyt::mf
