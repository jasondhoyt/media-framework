// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include "properties.hpp"

namespace jhoyt::mf
{

    class window;

    class window_create_properties final : public properties
    {
    public:
        void set_always_on_top(bool always_on_top);
        void set_borderless(bool borderless);
        void set_constrain_popup(bool constrain_popup);
        void set_external_graphics_context(bool external_graphics_context);
        void set_focusable(bool focusable);
        void set_height(int height);
        void set_hidden(bool hidden);
        void set_high_pixel_density(bool high_pixel_density);
        void set_maximized(bool maximized);
        void set_menu(bool menu);
        void set_metal(bool metal);
        void set_minimized(bool minimized);
        void set_modal(bool modal);
        void set_mouse_grabbed(bool mouse_grabbed);
        void set_opengl(bool opengl);
        void set_parent(const window& window);
        void set_resizable(bool resizable);
        void set_title(const std::string& title);
        void set_transparent(bool transparent);
        void set_tooltip(bool tooltip);
        void set_utility(bool utility);
        void set_vulkan(bool vulkan);
        void set_width(int width);
        void set_x(int x);
        void set_y(int y);
    };

} // namespace jhoyt::mf