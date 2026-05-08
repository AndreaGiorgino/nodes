#pragma once
#include <string>

#include "enviroment.hxx"
#include "raylib.h"

namespace gui {
    [[nodiscard]] auto measure_text(std::string_view text) noexcept -> ::Vector2;
    [[nodiscard]] auto wrap_text(std::string_view text, float maxWidth) noexcept -> std::string;

    auto draw_text(std::string_view text, ::Vector2 position, ::Color tint = ::BLACK, bool scaled = true) noexcept -> void;
} // namespace gui
