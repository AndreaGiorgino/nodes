#include <cmath>
#include <ranges>

#include "enviroment.hxx"
#include "gui.hxx"

namespace views = std::views;

namespace gui {
    auto measure_text(std::string_view text) noexcept -> ::Vector2 {
        if (text.empty())
            return {};

        const auto& env = enviroment::get_instance();
        const auto& camera = env.camera();
        const auto& [font, fontSize] = env.font();

        auto ret = ::MeasureTextEx(font, text.data(), fontSize, 1);
        ret.x /= camera.zoom;
        ret.y /= camera.zoom;
        return ret;
    }

    auto wrap_text(std::string_view text, float maxWidth) noexcept
        -> std::string {
            if (text.empty())
                return {};

            std::string ret {};
            std::string line {};
            for (const auto part : views::split(text, ' ')) {
                const std::string word { std::string_view { part } };
                const std::string testLine =
                    line.empty() ? word : (line + ' ' + word);

                const auto textSize = gui::measure_text(testLine);
                if (textSize.x >= maxWidth) {
                    ret += ret.empty() ? line : ('\n' + line);
                    line = word;
                } else line = std::move(testLine);
            }

            ret += ret.empty() ? line : ('\n' + line);
            return ret;
        }

    auto draw_text(std::string_view text, ::Vector2 position, ::Color tint,
            bool scaled) noexcept -> void {
            if (text.empty())
                return;

            const auto& env = enviroment::get_instance();
            const auto& [font, fontSize] = scaled
                ? env.font() : env.font_default();

            ::DrawTextEx(font, text.data(), position, fontSize, 1, tint);
        }
} // namespace gui
