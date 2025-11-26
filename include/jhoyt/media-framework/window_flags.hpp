// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_video.h>

#include "bitflags.hpp"

namespace jhoyt::mf
{

    enum class window_flag : uint64_t
    {
        fullscreen = SDL_WINDOW_FULLSCREEN,
        opengl = SDL_WINDOW_OPENGL,
        occluded = SDL_WINDOW_OCCLUDED,
        hidden = SDL_WINDOW_HIDDEN,
        borderless = SDL_WINDOW_BORDERLESS,
        resizable = SDL_WINDOW_RESIZABLE,
        minimized = SDL_WINDOW_MINIMIZED,
        maximized = SDL_WINDOW_MAXIMIZED,
        mouse_grabbed = SDL_WINDOW_MOUSE_GRABBED,
        input_focus = SDL_WINDOW_INPUT_FOCUS,
        external = SDL_WINDOW_EXTERNAL,
        modal = SDL_WINDOW_MODAL,
        high_pixel_density = SDL_WINDOW_HIGH_PIXEL_DENSITY,
        mouse_capture = SDL_WINDOW_MOUSE_CAPTURE,
        mouse_relative_mode = SDL_WINDOW_MOUSE_RELATIVE_MODE,
        always_on_top = SDL_WINDOW_ALWAYS_ON_TOP,
        utility = SDL_WINDOW_UTILITY,
        tooltip = SDL_WINDOW_TOOLTIP,
        popup_menu = SDL_WINDOW_POPUP_MENU,
        keyboard_grabbed = SDL_WINDOW_KEYBOARD_GRABBED,
        vulkan = SDL_WINDOW_VULKAN,
        metal = SDL_WINDOW_METAL,
        transparent = SDL_WINDOW_TRANSPARENT,
        not_focusable = SDL_WINDOW_NOT_FOCUSABLE
    };

    using window_flags = bitflags<window_flag, uint64_t>;

} // namespace jhoyt::mf
