// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <string>
#include <variant>
#include <vector>

#include <SDL3/SDL_properties.h>

namespace jhoyt::mf
{

    enum class property_type
    {
        invalid = SDL_PROPERTY_TYPE_INVALID,
        pointer = SDL_PROPERTY_TYPE_POINTER,
        string = SDL_PROPERTY_TYPE_STRING,
        number = SDL_PROPERTY_TYPE_NUMBER,
        real = SDL_PROPERTY_TYPE_FLOAT,
        boolean = SDL_PROPERTY_TYPE_BOOLEAN
    };

    using property_value = std::variant<std::monostate, void*, std::string, int64_t, float, bool>;

    inline property_type get_type(const property_value& value)
    {
        return static_cast<property_type>(value.index());
    }

    class properties
    {
    public:
        static properties get_global();

        properties();

        explicit properties(SDL_PropertiesID id, bool auto_destroy = true);

        virtual ~properties();

        properties(const properties&) = delete;
        properties& operator=(const properties&) = delete;

        properties(properties&& other) noexcept;
        properties& operator=(properties&& other) noexcept;

        [[nodiscard]] auto get_id() const
        {
            return id_;
        }

        void clear_property(const std::string& name);

        void copy_to(properties& props) const;

        [[nodiscard]] std::vector<std::string> get_property_names() const;

        [[nodiscard]] property_value get_property(const std::string& name) const;

        [[nodiscard]] property_type get_property_type(const std::string& name) const;

        [[nodiscard]] bool has_property(const std::string& name) const;

        void lock();

        void set_property(const std::string& name, const property_value& value);

        void unlock();

    private:
        SDL_PropertiesID id_;
        bool auto_destroy_;

        void destroy();
    };

} // namespace jhoyt::mf