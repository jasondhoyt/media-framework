// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <tuple>
#include <type_traits>

namespace jhoyt::mf
{

    template <typename T, typename... U>
    concept all_same_type = (... && std::is_same_v<T, U>);

    template <typename T, typename V> class bitflags final
    {
    public:
        static bitflags from_value(V value)
        {
            auto flags = bitflags{};
            flags.value_ = value;
            return flags;
        }

        bitflags() = default;

        template <typename... Args>
            requires all_same_type<T, Args...>
        bitflags(Args... args) : value_((static_cast<V>(args) | ...))
        {
        }

        [[nodiscard]] auto value() const
        {
            return value_;
        }

        [[nodiscard]] auto contains(T value) const
        {
            return (value_ & static_cast<V>(value)) != 0;
        }

    private:
        V value_ = 0;
    };

} // namespace jhoyt::mf
