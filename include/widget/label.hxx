#pragma once
#include <string>

#include "widget/base.hxx"

namespace widget {
    class label final : public widget::base {
        public:
            struct options {
                bool fitSize    { false };
                bool textScaled { false };
                bool textWrap   { false };
            };

        public:
            using base::base;

            label(::Rectangle rec, std::string_view text, label::options opts) noexcept;

            label(const label&) noexcept = default;
            auto operator =(const label&) noexcept -> label& = default;

            label(label&&) noexcept = default;
            auto operator =(label&&) noexcept -> label& = default;

            ~label(void) noexcept;

        public:
            using base::check_collision;

            auto render(void) const -> void override;
            auto update(void) -> void override;

        public:
            static struct style {
#ifdef DARK_THEME
                static inline constexpr ::Color textColor { ::RAYWHITE };
#else
                static inline constexpr ::Color textColor { ::BLACK };
#endif
            } style;

        private:
            std::string _text {};
            options _opts {};
    };
} // namespace widget
