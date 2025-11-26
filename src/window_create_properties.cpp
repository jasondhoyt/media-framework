// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>

#include <SDL3/SDL_video.h>

#include "jhoyt/media-framework/window_create_properties.hpp"

#include "jhoyt/media-framework/window.hpp"

namespace jhoyt::mf
{

    void window_create_properties::set_always_on_top(bool always_on_top)
    {
        set_property(SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN, always_on_top);
    }

    void window_create_properties::set_borderless(bool borderless)
    {
        set_property(SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN, borderless);
    }

    void window_create_properties::set_constrain_popup(bool constrain_popup)
    {
        set_property(SDL_PROP_WINDOW_CREATE_CONSTRAIN_POPUP_BOOLEAN, constrain_popup);
    }

    void window_create_properties::set_external_graphics_context(bool external_graphics_context)
    {
        set_property(SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, external_graphics_context);
    }

    void window_create_properties::set_focusable(bool focusable)
    {
        set_property(SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN, focusable);
    }

    void window_create_properties::set_height(int height)
    {
        set_property(SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
    }

    void window_create_properties::set_hidden(bool hidden)
    {
        set_property(SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN, hidden);
    }

    void window_create_properties::set_high_pixel_density(bool high_pixel_density)
    {
        set_property(SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, high_pixel_density);
    }

    void window_create_properties::set_maximized(bool maximized)
    {
        set_property(SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN, maximized);
    }

    void window_create_properties::set_menu(bool menu)
    {
        set_property(SDL_PROP_WINDOW_CREATE_MENU_BOOLEAN, menu);
    }

    void window_create_properties::set_metal(bool metal)
    {
        set_property(SDL_PROP_WINDOW_CREATE_METAL_BOOLEAN, metal);
    }

    void window_create_properties::set_minimized(bool minimized)
    {
        set_property(SDL_PROP_WINDOW_CREATE_MINIMIZED_BOOLEAN, minimized);
    }

    void window_create_properties::set_modal(bool modal)
    {
        set_property(SDL_PROP_WINDOW_CREATE_MODAL_BOOLEAN, modal);
    }

    void window_create_properties::set_mouse_grabbed(bool mouse_grabbed)
    {
        set_property(SDL_PROP_WINDOW_CREATE_MOUSE_GRABBED_BOOLEAN, mouse_grabbed);
    }

    void window_create_properties::set_opengl(bool opengl)
    {
        set_property(SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, opengl);
    }
    void window_create_properties::set_parent(const window& window)
    {
        assert(window.get_ptr());
        set_property(SDL_PROP_WINDOW_CREATE_PARENT_POINTER, window.get_ptr());
    }

    void window_create_properties::set_resizable(bool resizable)
    {
        set_property(SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, resizable);
    }

    void window_create_properties::set_title(const std::string& title)
    {
        set_property(SDL_PROP_WINDOW_CREATE_TITLE_STRING, title.c_str());
    }

    void window_create_properties::set_transparent(bool transparent)
    {
        set_property(SDL_PROP_WINDOW_CREATE_TRANSPARENT_BOOLEAN, transparent);
    }

    void window_create_properties::set_tooltip(bool tooltip)
    {
        set_property(SDL_PROP_WINDOW_CREATE_TOOLTIP_BOOLEAN, tooltip);
    }

    void window_create_properties::set_utility(bool utility)
    {
        set_property(SDL_PROP_WINDOW_CREATE_UTILITY_BOOLEAN, utility);
    }

    void window_create_properties::set_vulkan(bool vulkan)
    {
        set_property(SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN, vulkan);
    }

    void window_create_properties::set_width(int width)
    {
        set_property(SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
    }

    void window_create_properties::set_x(int x)
    {
        set_property(SDL_PROP_WINDOW_CREATE_X_NUMBER, x);
    }

    void window_create_properties::set_y(int y)
    {
        set_property(SDL_PROP_WINDOW_CREATE_Y_NUMBER, y);
    }

} // namespace jhoyt::mf