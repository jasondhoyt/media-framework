// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/media-framework/window.hpp"

namespace jhoyt::mf
{

    window window::get_from_id(const SDL_WindowID id)
    {
        auto ptr = SDL_GetWindowFromID(id);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {ptr, false};
    }

    window::window(const std::string& title, const int w, const int h, const window_flags flags)
        : ptr_(SDL_CreateWindow(title.c_str(), w, h, flags.value()))
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    window::window(const window_create_properties& props) : ptr_(SDL_CreateWindowWithProperties(props.get_id()))
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    window::window(SDL_Window* ptr, bool auto_destroy) : ptr_(ptr), auto_destroy_(auto_destroy)
    {
    }

    window::~window()
    {
        destroy();
    }

    window::window(window&& other) noexcept : ptr_(other.ptr_), auto_destroy_(other.auto_destroy_)
    {
        other.ptr_ = nullptr;
    }

    window& window::operator=(window&& other) noexcept
    {
        if (this != &other)
        {
            destroy();

            std::swap(ptr_, other.ptr_);
            std::swap(auto_destroy_, other.auto_destroy_);
        }

        return *this;
    }

    void window::destroy()
    {
        if (ptr_ && auto_destroy_)
        {
            SDL_DestroyWindow(ptr_);
        }

        ptr_ = nullptr;
    }

    void window::flash(flash_operation operation)
    {
        assert(ptr_);

        if (!SDL_FlashWindow(ptr_, static_cast<SDL_FlashOperation>(operation)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    window::aspect_ratio window::get_aspect_ratio() const
    {
        assert(ptr_);

        auto ratio = aspect_ratio{};
        if (!SDL_GetWindowAspectRatio(ptr_, &ratio.min, &ratio.max))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return ratio;
    }

    window::borders_size window::get_borders_size() const
    {
        assert(ptr_);

        auto borders = borders_size{};
        if (!SDL_GetWindowBordersSize(ptr_, &borders.top, &borders.left, &borders.bottom, &borders.right))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return borders;
    }

    float window::get_display_scale() const
    {
        assert(ptr_);

        const auto scale = SDL_GetWindowDisplayScale(ptr_);
        if (scale == 0.0f)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return scale;
    }

    window_flags window::get_flags() const
    {
        assert(ptr_);
        return window_flags::from_value(SDL_GetWindowFlags(ptr_));
    }

    const SDL_DisplayMode* window::get_fullscreen_mode() const
    {
        assert(ptr_);
        return SDL_GetWindowFullscreenMode(ptr_);
    }

    SDL_WindowID window::get_id() const
    {
        assert(ptr_);

        const auto id = SDL_GetWindowID(ptr_);
        if (id == 0)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return id;
    }

    bool window::get_keyboard_grab() const
    {
        assert(ptr_);
        return SDL_GetWindowKeyboardGrab(ptr_);
    }

    size window::get_maximum_size() const
    {
        assert(ptr_);

        auto w = 0;
        auto h = 0;
        if (!SDL_GetWindowMaximumSize(ptr_, &w, &h))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {w, h};
    }

    size window::get_minimum_size() const
    {
        assert(ptr_);

        auto w = 0;
        auto h = 0;
        if (!SDL_GetWindowMinimumSize(ptr_, &w, &h))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {w, h};
    }

    bool window::get_mouse_grab() const
    {
        assert(ptr_);
        return SDL_GetWindowMouseGrab(ptr_);
    }

    std::optional<rect> window::get_mouse_rect() const
    {
        assert(ptr_);

        const auto r = SDL_GetWindowMouseRect(ptr_);
        if (!r)
        {
            return {};
        }

        return rect{*r};
    }

    float window::get_opacity() const
    {
        assert(ptr_);

        const auto opacity = SDL_GetWindowOpacity(ptr_);
        if (opacity == -1.0f)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return opacity;
    }

    std::optional<window> window::get_parent() const
    {
        assert(ptr_);

        const auto ptr = SDL_GetWindowParent(ptr_);
        if (!ptr)
        {
            return {};
        }

        return window{ptr, false};
    }

    float window::get_pixel_density() const
    {
        assert(ptr_);

        const auto pixel_density = SDL_GetWindowPixelDensity(ptr_);
        if (pixel_density == 0.0f)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return pixel_density;
    }

    pixel_format window::get_pixel_format() const
    {
        assert(ptr_);

        auto format = SDL_GetWindowPixelFormat(ptr_);
        if (format == SDL_PIXELFORMAT_UNKNOWN)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return static_cast<pixel_format>(format);
    }

    point window::get_position() const
    {
        assert(ptr_);

        auto x = 0;
        auto y = 0;
        if (!SDL_GetWindowPosition(ptr_, &x, &y))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {x, y};
    }

    window_properties window::get_properties() const
    {
        assert(ptr_);

        const auto id = SDL_GetWindowProperties(ptr_);
        if (id == 0)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return window_properties{id};
    }

    rect window::get_safe_area() const
    {
        assert(ptr_);

        auto r = SDL_Rect{0};
        if (!SDL_GetWindowSafeArea(ptr_, &r))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {r};
    }

    size window::get_size() const
    {
        assert(ptr_);

        auto w = 0;
        auto h = 0;
        if (!SDL_GetWindowSize(ptr_, &w, &h))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {w, h};
    }

    size window::get_size_in_pixels() const
    {
        assert(ptr_);

        auto w = 0;
        auto h = 0;
        if (!SDL_GetWindowSizeInPixels(ptr_, &w, &h))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {w, h};
    }

    surface window::get_surface() const
    {
        assert(ptr_);

        auto ptr = SDL_GetWindowSurface(ptr_);
        if (!ptr)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {ptr, false};
    }

    int window::get_surface_vsync() const
    {
        assert(ptr_);

        auto vsync = 0;
        if (!SDL_GetWindowSurfaceVSync(ptr_, &vsync))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return vsync;
    }

    std::string window::get_title() const
    {
        assert(ptr_);

        const auto title = SDL_GetWindowTitle(ptr_);
        if (!title)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return title;
    }

    void window::hide()
    {
        assert(ptr_);

        if (!SDL_HideWindow(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::maximize()
    {
        assert(ptr_);

        if (!SDL_MaximizeWindow(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::minimize()
    {
        assert(ptr_);

        if (!SDL_MinimizeWindow(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::raise()
    {
        assert(ptr_);

        if (!SDL_RaiseWindow(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::restore()
    {
        assert(ptr_);

        if (!SDL_RestoreWindow(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_always_on_top(const bool on_top)
    {
        assert(ptr_);

        if (!SDL_SetWindowAlwaysOnTop(ptr_, on_top))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_aspect_ratio(const aspect_ratio& ratio)
    {
        assert(ptr_);

        if (!SDL_SetWindowAspectRatio(ptr_, ratio.min, ratio.max))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_bordered(const bool bordered)
    {
        assert(ptr_);

        if (!SDL_SetWindowBordered(ptr_, bordered))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_focusable(const bool focusable)
    {
        assert(ptr_);

        if (!SDL_SetWindowFocusable(ptr_, focusable))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_fullscreen(const bool fullscreen)
    {
        assert(ptr_);

        if (!SDL_SetWindowFullscreen(ptr_, fullscreen))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_fullscreen_mode(const SDL_DisplayMode* mode)
    {
        assert(ptr_);

        if (!SDL_SetWindowFullscreenMode(ptr_, mode))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_icon(const surface& icon)
    {
        assert(ptr_);
        assert(icon.get_ptr());

        if (!SDL_SetWindowIcon(ptr_, icon.get_ptr()))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_keyboard_grabbed(const bool grabbed)
    {
        assert(ptr_);

        if (!SDL_SetWindowKeyboardGrab(ptr_, grabbed))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_maximum_size(const size& size)
    {
        assert(ptr_);

        if (!SDL_SetWindowMaximumSize(ptr_, size.w, size.h))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_minimum_size(const size& size)
    {
        assert(ptr_);

        if (!SDL_SetWindowMinimumSize(ptr_, size.w, size.h))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_modal(const bool modal)
    {
        assert(ptr_);

        if (!SDL_SetWindowModal(ptr_, modal))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_mouse_grabbed(const bool grabbed)
    {
        assert(ptr_);

        if (!SDL_SetWindowMouseGrab(ptr_, grabbed))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_mouse_rect(const std::optional<rect>& rect)
    {
        assert(ptr_);

        if (!SDL_SetWindowMouseRect(ptr_, rect ? &(*rect) : nullptr))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_opacity(const float opacity)
    {
        assert(ptr_);

        if (!SDL_SetWindowOpacity(ptr_, opacity))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_parent(const window& parent)
    {
        assert(ptr_);
        assert(parent.ptr_);

        if (!SDL_SetWindowParent(ptr_, parent.ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_position(const std::optional<point>& at)
    {
        assert(ptr_);

        if (!SDL_SetWindowPosition(ptr_, at ? at->x : SDL_WINDOWPOS_UNDEFINED, at ? at->y : SDL_WINDOWPOS_UNDEFINED))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_centered(const SDL_DisplayID display_id)
    {
        assert(ptr_);

        if (!SDL_SetWindowPosition(
                ptr_, SDL_WINDOWPOS_CENTERED_DISPLAY(display_id), SDL_WINDOWPOS_CENTERED_DISPLAY(display_id)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_resizable(const bool resizable)
    {
        assert(ptr_);

        if (!SDL_SetWindowResizable(ptr_, resizable))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_shape(const surface& shape)
    {
        assert(ptr_);

        if (!SDL_SetWindowShape(ptr_, shape.get_ptr()))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_size(const size& size)
    {
        assert(ptr_);

        if (!SDL_SetWindowSize(ptr_, size.w, size.h))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_surface_vsync(const int vsync)
    {
        assert(ptr_);

        if (!SDL_SetWindowSurfaceVSync(ptr_, vsync))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::set_title(const std::string& title)
    {
        assert(ptr_);

        if (!SDL_SetWindowTitle(ptr_, title.c_str()))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::show()
    {
        assert(ptr_);

        if (!SDL_ShowWindow(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::show_system_menu(const point& at)
    {
        assert(ptr_);

        if (!SDL_ShowWindowSystemMenu(ptr_, at.x, at.y))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::sync()
    {
        assert(ptr_);

        if (!SDL_SyncWindow(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::update_surface()
    {
        assert(ptr_);

        if (!SDL_UpdateWindowSurface(ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void window::update_surface_rects(std::span<const rect> rects)
    {
        assert(ptr_);

        if (!SDL_UpdateWindowSurfaceRects(ptr_, rects.data(), static_cast<int>(rects.size())))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    bool window::has_surface() const
    {
        assert(ptr_);
        return SDL_WindowHasSurface(ptr_);
    }

} // namespace jhoyt::mf