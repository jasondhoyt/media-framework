// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <optional>
#include <string>

#include <SDL3/SDL_video.h>

#include "pixel_format.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "size.hpp"
#include "surface.hpp"
#include "window_create_properties.hpp"
#include "window_flags.hpp"
#include "window_properties.hpp"

namespace jhoyt::mf
{

    enum class flash_operation
    {
        cancel = SDL_FLASH_CANCEL,
        briefly = SDL_FLASH_BRIEFLY,
        until_focused = SDL_FLASH_UNTIL_FOCUSED
    };

    class window final
    {
    public:
        static window get_from_id(SDL_WindowID id);

        window() = default;
        window(const std::string& title, int w, int h, window_flags flags);
        explicit window(const window_create_properties& props);
        window(SDL_Window* ptr, bool auto_destroy);
        ~window();

        window(const window&) = delete;
        window& operator=(const window&) = delete;

        window(window&& other) noexcept;
        window& operator=(window&& other) noexcept;

        void destroy();

        void flash(flash_operation operation);

        struct aspect_ratio
        {
            float min;
            float max;
        };

        [[nodiscard]] aspect_ratio get_aspect_ratio() const;

        struct borders_size
        {
            int top;
            int left;
            int bottom;
            int right;
        };

        [[nodiscard]] borders_size get_borders_size() const;
        [[nodiscard]] float get_display_scale() const;
        [[nodiscard]] window_flags get_flags() const;
        [[nodiscard]] const SDL_DisplayMode* get_fullscreen_mode() const;
        [[nodiscard]] SDL_WindowID get_id() const;
        [[nodiscard]] bool get_keyboard_grab() const;
        [[nodiscard]] size get_maximum_size() const;
        [[nodiscard]] size get_minimum_size() const;
        [[nodiscard]] bool get_mouse_grab() const;
        [[nodiscard]] std::optional<rect> get_mouse_rect() const;
        [[nodiscard]] float get_opacity() const;
        [[nodiscard]] std::optional<window> get_parent() const;
        [[nodiscard]] float get_pixel_density() const;
        [[nodiscard]] pixel_format get_pixel_format() const;
        [[nodiscard]] point get_position() const;
        [[nodiscard]] window_properties get_properties() const;
        [[nodiscard]] rect get_safe_area() const;
        [[nodiscard]] size get_size() const;
        [[nodiscard]] size get_size_in_pixels() const;
        [[nodiscard]] surface get_surface() const;
        [[nodiscard]] int get_surface_vsync() const;
        [[nodiscard]] std::string get_title() const;

        void hide();
        void maximize();
        void minimize();
        void raise();
        void restore();

        void set_always_on_top(bool on_top);
        void set_aspect_ratio(const aspect_ratio& ratio);
        void set_bordered(bool bordered);
        void set_focusable(bool focusable);
        void set_fullscreen(bool fullscreen);
        void set_fullscreen_mode(const SDL_DisplayMode* mode);
        void set_icon(const surface& icon);
        void set_keyboard_grabbed(bool grabbed);
        void set_maximum_size(const size& size);
        void set_minimum_size(const size& size);
        void set_modal(bool modal);
        void set_mouse_grabbed(bool grabbed);
        void set_mouse_rect(const std::optional<rect>& rect);
        void set_opacity(float opacity);
        void set_parent(const window& parent);
        void set_position(const std::optional<point>& at);
        void set_centered(SDL_DisplayID display_id = 0);
        void set_resizable(bool resizable);
        void set_shape(const surface& shape);
        void set_size(const size& size);
        void set_surface_vsync(int vsync);
        void set_title(const std::string& title);

        void show();
        void show_system_menu(const point& at);
        void sync();
        void update_surface();
        void update_surface_rects(std::span<const rect> rects);

        [[nodiscard]] bool has_surface() const;

        [[nodiscard]] auto get_ptr() const
        {
            return ptr_;
        }

    private:
        SDL_Window* ptr_ = nullptr;
        bool auto_destroy_ = true;
    };

} // namespace jhoyt::mf