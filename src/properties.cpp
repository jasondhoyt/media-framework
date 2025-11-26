// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/media-framework/properties.hpp"

namespace
{

    void enumerate_properties_cb(void* data, SDL_PropertiesID id, const char* name)
    {
        auto& names = *static_cast<std::vector<std::string>*>(data);
        names.emplace_back(name);
    }

} // namespace

namespace jhoyt::mf
{

    properties properties::get_global()
    {
        return properties{SDL_GetGlobalProperties(), false};
    }

    properties::properties() : id_(SDL_CreateProperties()), auto_destroy_(true)
    {
        if (id_ == 0)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    properties::properties(const SDL_PropertiesID id, const bool auto_destroy) : id_(id), auto_destroy_(auto_destroy)
    {
    }

    properties::~properties()
    {
        destroy();
    }

    properties::properties(properties&& other) noexcept : id_(other.id_), auto_destroy_(other.auto_destroy_)
    {
        other.id_ = 0;
        other.auto_destroy_ = true;
    }

    properties& properties::operator=(properties&& other) noexcept
    {
        if (this != &other)
        {
            destroy();

            std::swap(id_, other.id_);
            std::swap(auto_destroy_, other.auto_destroy_);
        }

        return *this;
    }

    void properties::clear_property(const std::string& name)
    {
        assert(id_ > 0);
        if (!SDL_ClearProperty(id_, name.c_str()))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void properties::copy_to(properties& props) const
    {
        assert(id_ > 0);
        assert(props.id_ > 0);

        if (!SDL_CopyProperties(id_, props.id_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    std::vector<std::string> properties::get_property_names() const
    {
        assert(id_ > 0);

        thread_local auto names = std::vector<std::string>{};
        names.clear();

        if (!SDL_EnumerateProperties(id_, enumerate_properties_cb, &names))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return names;
    }

    property_value properties::get_property(const char* name) const
    {
        assert(id_ > 0);

        switch (static_cast<property_type>(SDL_GetPropertyType(id_, name)))
        {
        case property_type::invalid:
            return {};

        case property_type::pointer:
            return SDL_GetPointerProperty(id_, name, nullptr);

        case property_type::string:
            return SDL_GetStringProperty(id_, name, "");

        case property_type::number:
            return SDL_GetNumberProperty(id_, name, 0);

        case property_type::real:
            return SDL_GetFloatProperty(id_, name, 0.0f);

        case property_type::boolean:
            return SDL_GetBooleanProperty(id_, name, false);

        default:
            assert(false);
        }
    }

    property_value properties::get_property(const std::string& name) const
    {
        return get_property(name.c_str());
    }

    property_type properties::get_property_type(const std::string& name) const
    {
        assert(id_ > 0);
        return static_cast<property_type>(SDL_GetPropertyType(id_, name.c_str()));
    }

    bool properties::has_property(const std::string& name) const
    {
        assert(id_ > 0);
        return get_property_type(name) != property_type::invalid;
    }

    void properties::lock()
    {
        assert(id_ > 0);
        if (!SDL_LockProperties(id_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void properties::set_property(const char* name, const property_value& value)
    {
        switch (get_type(value))
        {
        case property_type::invalid:
            break;

        case property_type::pointer:
            if (!SDL_SetPointerProperty(id_, name, *std::get_if<void*>(&value)))
            {
                throw std::runtime_error{SDL_GetError()};
            }
            break;

        case property_type::string:
            if (!SDL_SetStringProperty(id_, name, std::get_if<std::string>(&value)->c_str()))
            {
                throw std::runtime_error{SDL_GetError()};
            }
            break;

        case property_type::number:
            if (!SDL_SetNumberProperty(id_, name, *std::get_if<int64_t>(&value)))
            {
                throw std::runtime_error{SDL_GetError()};
            }
            break;

        case property_type::real:
            if (!SDL_SetFloatProperty(id_, name, *std::get_if<float>(&value)))
            {
                throw std::runtime_error{SDL_GetError()};
            }
            break;

        case property_type::boolean:
            if (!SDL_SetBooleanProperty(id_, name, *std::get_if<bool>(&value)))
            {
                throw std::runtime_error{SDL_GetError()};
            }
            break;

        default:
            assert(false);
        }
    }

    void properties::set_property(const std::string& name, const property_value& value)
    {
        set_property(name.c_str(), value);
    }

    void properties::unlock()
    {
        assert(id_ > 0);
        SDL_UnlockProperties(id_);
    }

    void properties::destroy()
    {
        if (id_ != 0 && auto_destroy_)
        {
            SDL_DestroyProperties(id_);
        }

        id_ = 0;
    }

} // namespace jhoyt::mf