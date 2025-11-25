// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <span>

#include <SDL3/SDL_surface.h>

#include "blend_mode.hpp"
#include "color.hpp"
#include "colorspace.hpp"
#include "fcolor.hpp"
#include "flip_mode.hpp"
#include "palette.hpp"
#include "pixel_format.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "rgb.hpp"
#include "scale_mode.hpp"
#include "surface_properties.hpp"

namespace jhoyt::mf
{

    class surface final
    {
    public:
        surface() = default;
        surface(SDL_Surface* ptr, bool auto_destroy);
        surface(int width, int height, pixel_format format);
        surface(int width, int height, pixel_format format, std::span<const char> pixels, int pitch);
        explicit surface(const std::string& path);
        explicit surface(std::span<const char> data);
        ~surface();

        surface(const surface&) = delete;
        surface& operator=(const surface&) = delete;

        surface(surface&& other) noexcept;
        surface& operator=(surface&& other) noexcept;

        void add_alternate_image(const surface& image);

        void blit(surface& dest) const;
        void blit(surface& dest, const point& at) const;
        void blit(const rect& src_bounds, surface& dest, const point& at) const;

        void blit_9grid(const rect& src_bounds,
                        int left_width,
                        int right_width,
                        int top_height,
                        int bottom_height,
                        float scale,
                        scale_mode mode,
                        surface& dest,
                        const rect& dest_bounds) const;

        void blit_scaled(surface& dest, scale_mode mode) const;
        void blit_scaled(surface& dest, const rect& dest_bounds, scale_mode mode) const;
        void blit_scaled(const rect& src_bounds, surface& dest, const rect& dest_bounds, scale_mode mode) const;

        void blit_tiled(surface& dest) const;
        void blit_tiled(surface& dest, const rect& dest_bounds) const;
        void blit_tiled(const rect& src_bounds, surface& dest, const rect& dest_bounds) const;

        void blit_tiled_with_scale(float scale, scale_mode mode, surface& dest, const rect& dest_bounds) const;
        void blit_tiled_with_scale(
            const rect& src_bounds, float scale, scale_mode mode, surface& dest, const rect& dest_bounds) const;

        void clear(const fcolor& color);

        [[nodiscard]] surface convert(pixel_format format) const;

        void destroy();

        [[nodiscard]] surface duplicate() const;

        void fill_rect(const rect& rect, const color& color);
        void fill_rects(std::span<const rect> rects, const color& color);

        void flip(flip_mode mode);

        [[nodiscard]] uint8_t get_alpha_mod() const;
        [[nodiscard]] blend_mode get_blend_mode() const;
        [[nodiscard]] rect get_clip_rect() const;
        [[nodiscard]] std::optional<uint32_t> get_color_key() const;
        [[nodiscard]] rgb get_color_mod() const;
        [[nodiscard]] colorspace get_colorspace() const;
        [[nodiscard]] std::vector<surface> get_images() const;
        [[nodiscard]] palette get_palette() const;
        [[nodiscard]] surface_properties get_properties() const;

        [[nodiscard]] color read_pixel(int x, int y) const;
        [[nodiscard]] fcolor read_pixel_float(int x, int y) const;

        void remove_alternate_images();

        void save_bmp(const std::string& path);

        surface scale_surface(int width, int height, scale_mode mode);

        void set_alpha_mod(uint8_t alpha);
        void set_blend_mode(blend_mode mode);
        void set_clip_rect(const rect& rect);
        void set_color_key(std::optional<uint32_t> key);
        void set_color_mod(const rgb& rgb);
        void set_colorspace(colorspace colorspace);
        void set_palette(const palette& palette);
        void set_rle(bool enabled);

        [[nodiscard]] bool has_alternate_images() const;
        [[nodiscard]] bool has_rle() const;
        [[nodiscard]] bool has_color_key() const;

        void write_pixel(int x, int y, const color& color);
        void write_pixel(int x, int y, const fcolor& color);

        [[nodiscard]] auto get_ptr() const
        {
            return ptr_;
        }

    private:
        SDL_Surface* ptr_ = nullptr;
        bool auto_destroy_ = true;
    };

} // namespace jhoyt::mf
