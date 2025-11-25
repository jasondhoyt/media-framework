// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/media-framework/surface.hpp"

namespace jhoyt::mf
{

    surface::surface(const int width, const int height, pixel_format format)
        : ptr_(SDL_CreateSurface(width, height, static_cast<SDL_PixelFormat>(format)))
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    surface::surface(
        const int width, const int height, pixel_format format, std::span<const char> pixels, const int pitch)
        : ptr_(SDL_CreateSurfaceFrom(
              width, height, static_cast<SDL_PixelFormat>(format), const_cast<char*>(pixels.data()), pitch))
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    surface::surface(SDL_Surface* ptr, const bool auto_destroy) : ptr_(ptr), auto_destroy_(auto_destroy)
    {
    }

    surface::surface(const std::string& path) : ptr_(SDL_LoadBMP(path.c_str())) // TODO : pull in SDL_image?
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    surface::surface(const std::span<const char> data)
    {
        const auto io = SDL_IOFromConstMem(data.data(), data.size());
        if (!io)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        ptr_ = SDL_LoadBMP_IO(io, true);
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    surface::~surface()
    {
        destroy();
    }

    surface::surface(surface&& other) noexcept : ptr_(other.ptr_), auto_destroy_(other.auto_destroy_)
    {
        other.ptr_ = nullptr;
    }

    surface& surface::operator=(surface&& other) noexcept
    {
        if (this != &other)
        {
            destroy();

            std::swap(ptr_, other.ptr_);
            std::swap(auto_destroy_, other.auto_destroy_);
        }

        return *this;
    }

    void surface::add_alternate_image(const surface& image)
    {
        assert(ptr_);
        assert(image.ptr_);

        if (!SDL_AddSurfaceAlternateImage(ptr_, image.ptr_))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit(surface& dest) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurface(ptr_, nullptr, dest.ptr_, nullptr))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit(surface& dest, const point& at) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        const auto dest_rect = SDL_Rect{at.x, at.y};
        if (!SDL_BlitSurface(ptr_, nullptr, dest.ptr_, &dest_rect))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit(const rect& src_bounds, surface& dest, const point& at) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        const auto dest_rect = SDL_Rect{at.x, at.y};
        if (!SDL_BlitSurface(ptr_, &src_bounds, dest.ptr_, &dest_rect))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_9grid(const rect& src_bounds,
                             int left_width,
                             int right_width,
                             int top_height,
                             int bottom_height,
                             float scale,
                             scale_mode mode,
                             surface& dest,
                             const rect& dest_bounds) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurface9Grid(ptr_,
                                  &src_bounds,
                                  left_width,
                                  right_width,
                                  top_height,
                                  bottom_height,
                                  scale,
                                  static_cast<SDL_ScaleMode>(mode),
                                  dest.ptr_,
                                  &dest_bounds))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_scaled(surface& dest, scale_mode mode) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceScaled(ptr_, nullptr, dest.ptr_, nullptr, static_cast<SDL_ScaleMode>(mode)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_scaled(surface& dest, const rect& dest_bounds, scale_mode mode) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceScaled(ptr_, nullptr, dest.ptr_, &dest_bounds, static_cast<SDL_ScaleMode>(mode)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_scaled(const rect& src_bounds, surface& dest, const rect& dest_bounds, scale_mode mode) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceScaled(ptr_, &src_bounds, dest.ptr_, &dest_bounds, static_cast<SDL_ScaleMode>(mode)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_tiled(surface& dest) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceTiled(ptr_, nullptr, dest.ptr_, nullptr))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_tiled(surface& dest, const rect& dest_bounds) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceTiled(ptr_, nullptr, dest.ptr_, &dest_bounds))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }
    void surface::blit_tiled(const rect& src_bounds, surface& dest, const rect& dest_bounds) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceTiled(ptr_, &src_bounds, dest.ptr_, &dest_bounds))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_tiled_with_scale(float scale, scale_mode mode, surface& dest, const rect& dest_bounds) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceTiledWithScale(
                ptr_, nullptr, scale, static_cast<SDL_ScaleMode>(mode), dest.ptr_, &dest_bounds))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::blit_tiled_with_scale(
        const rect& src_bounds, float scale, scale_mode mode, surface& dest, const rect& dest_bounds) const
    {
        assert(ptr_);
        assert(dest.ptr_);

        if (!SDL_BlitSurfaceTiledWithScale(
                ptr_, &src_bounds, scale, static_cast<SDL_ScaleMode>(mode), dest.ptr_, &dest_bounds))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::clear(const fcolor& color)
    {
        assert(ptr_);

        if (!SDL_ClearSurface(ptr_, color.r, color.g, color.b, color.a))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    surface surface::convert(pixel_format format) const
    {
        assert(ptr_);

        auto new_surface = surface{};
        new_surface.ptr_ = SDL_ConvertSurface(ptr_, static_cast<SDL_PixelFormat>(format));
        if (!new_surface.ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return new_surface;
    }

    void surface::destroy()
    {
        if (ptr_ && auto_destroy_)
        {
            SDL_DestroySurface(ptr_);
        }

        ptr_ = nullptr;
    }

    surface surface::duplicate() const
    {
        assert(ptr_);

        auto new_surface = surface{};
        new_surface.ptr_ = SDL_DuplicateSurface(ptr_);
        if (!new_surface.ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return new_surface;
    }

    void surface::fill_rect(const rect& rect, const color& color)
    {
        assert(ptr_);

        if (!SDL_FillSurfaceRect(ptr_, &rect, SDL_MapSurfaceRGBA(ptr_, color.r, color.g, color.b, color.a)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::fill_rects(std::span<const rect> rects, const color& color)
    {
        assert(ptr_);

        if (!SDL_FillSurfaceRects(ptr_,
                                  rects.data(),
                                  static_cast<int>(rects.size()),
                                  SDL_MapSurfaceRGBA(ptr_, color.r, color.g, color.b, color.a)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::flip(flip_mode mode)
    {
        assert(ptr_);

        if (!SDL_FlipSurface(ptr_, static_cast<SDL_FlipMode>(mode)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    uint8_t surface::get_alpha_mod() const
    {
        assert(ptr_);

        auto alpha = uint8_t{0};
        if (!SDL_GetSurfaceAlphaMod(ptr_, &alpha))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return alpha;
    }

    blend_mode surface::get_blend_mode() const
    {
        assert(ptr_);

        auto bmode = SDL_BlendMode{0};
        if (!SDL_GetSurfaceBlendMode(ptr_, &bmode))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return blend_mode{bmode};
    }

    rect surface::get_clip_rect() const
    {
        assert(ptr_);

        auto r = SDL_Rect{0};
        if (!SDL_GetSurfaceClipRect(ptr_, &r))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {r};
    }

    std::optional<uint32_t> surface::get_color_key() const
    {
        assert(ptr_);

        auto key = uint32_t{0};
        if (!SDL_GetSurfaceColorKey(ptr_, &key))
        {
            return {};
        }

        return key;
    }

    rgb surface::get_color_mod() const
    {
        assert(ptr_);

        auto color = rgb{0};
        if (!SDL_GetSurfaceColorMod(ptr_, &color.r, &color.g, &color.b))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return color;
    }

    colorspace surface::get_colorspace() const
    {
        assert(ptr_);
        return static_cast<colorspace>(SDL_GetSurfaceColorspace(ptr_));
    }

    std::vector<surface> surface::get_images() const
    {
        assert(ptr_);

        auto count = 0;
        const auto images = SDL_GetSurfaceImages(ptr_, &count);
        if (!images)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        auto surfaces = std::vector<surface>{};
        for (auto i = 0; i < count; ++i)
        {
            surfaces.emplace_back(images[i], false);
        }
        SDL_free(images);

        return surfaces;
    }

    palette surface::get_palette() const
    {
        assert(ptr_);

        auto pal = SDL_GetSurfacePalette(ptr_);
        if (!pal)
        {
            return {};
        }

        return {pal, false};
    }

    surface_properties surface::get_properties() const
    {
        assert(ptr_);

        auto id = SDL_GetSurfaceProperties(ptr_);
        if (id == 0)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return {id};
    }

    color surface::read_pixel(const int x, const int y) const
    {
        assert(ptr_);

        auto col = color{};
        if (!SDL_ReadSurfacePixel(ptr_, x, y, &col.r, &col.g, &col.b, &col.a))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return col;
    }

    fcolor surface::read_pixel_float(const int x, const int y) const
    {
        assert(ptr_);

        auto col = fcolor{};
        if (!SDL_ReadSurfacePixelFloat(ptr_, x, y, &col.r, &col.g, &col.b, &col.a))
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return col;
    }

    void surface::remove_alternate_images()
    {
        assert(ptr_);
        SDL_RemoveSurfaceAlternateImages(ptr_);
    }

    void surface::save_bmp(const std::string& path)
    {
        assert(ptr_);

        if (!SDL_SaveBMP(ptr_, path.c_str()))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    surface surface::scale_surface(int width, int height, scale_mode mode)
    {
        assert(ptr_);

        auto new_surface = surface{};
        new_surface.ptr_ = SDL_ScaleSurface(ptr_, width, height, static_cast<SDL_ScaleMode>(mode));
        if (!new_surface.ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }

        return new_surface;
    }

    void surface::set_alpha_mod(uint8_t alpha)
    {
        assert(ptr_);

        if (!SDL_SetSurfaceAlphaMod(ptr_, alpha))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::set_blend_mode(blend_mode mode)
    {
        assert(ptr_);

        if (!SDL_SetSurfaceBlendMode(ptr_, mode.get_value()))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::set_clip_rect(const rect& rect)
    {
        assert(ptr_);

        if (!SDL_SetSurfaceClipRect(ptr_, &rect))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::set_color_key(std::optional<uint32_t> key)
    {
        assert(ptr_);

        if (!SDL_SetSurfaceColorKey(ptr_, key.has_value(), key.value_or(0)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::set_color_mod(const rgb& rgb)
    {
        assert(ptr_);

        if (!SDL_SetSurfaceColorMod(ptr_, rgb.r, rgb.g, rgb.b))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::set_colorspace(colorspace colorspace)
    {
        assert(ptr_);

        if (!SDL_SetSurfaceColorspace(ptr_, static_cast<SDL_Colorspace>(colorspace)))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::set_palette(const palette& palette)
    {
        assert(ptr_);
        assert(palette.get_ptr());

        if (!SDL_SetSurfacePalette(ptr_, palette.get_ptr()))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::set_rle(bool enabled)
    {
        assert(ptr_);

        if (!SDL_SetSurfaceRLE(ptr_, enabled))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    bool surface::has_alternate_images() const
    {
        assert(ptr_);
        return SDL_SurfaceHasAlternateImages(ptr_);
    }

    bool surface::has_rle() const
    {
        assert(ptr_);
        return SDL_SurfaceHasRLE(ptr_);
    }

    bool surface::has_color_key() const
    {
        assert(ptr_);
        return SDL_SurfaceHasColorKey(ptr_);
    }

    void surface::write_pixel(int x, int y, const color& color)
    {
        assert(ptr_);

        if (!SDL_WriteSurfacePixel(ptr_, x, y, color.r, color.g, color.b, color.a))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    void surface::write_pixel(int x, int y, const fcolor& color)
    {
        assert(ptr_);

        if (!SDL_WriteSurfacePixelFloat(ptr_, x, y, color.r, color.g, color.b, color.a))
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

} // namespace jhoyt::mf