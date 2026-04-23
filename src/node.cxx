#include "enviroment.hxx"
#include "gui.hxx"
#include "node.hxx"
#include "raylib.h"

node::node(void)
    noexcept {
        // empty
    }

node::node(std::string_view title, std::string_view description, ::Vector2 pos)
    noexcept : _pos(std::move(pos)) {
        const float maxWidth = width - padding * 2;
        _title = node_text {
            .text = std::string { title },
            .wrapped = gui::wrap_text(title, maxWidth),
        };

        _description = node_text {
            .text = std::string { description },
            .wrapped = gui::wrap_text(description, maxWidth),
        };
    }

auto node::update(void)
    noexcept -> void {
        // TODO: update node
    }

auto node::render(void)
    const noexcept -> void {
        const auto titleSize = gui::draw_text_rec(_title.wrapped, _pos, width,
                padding, ::ColorAlpha(::BLUE, 0.2f));

        const ::Vector2 descriptionPos {
            _pos.x,
            _pos.y + titleSize.y
        };

        gui::draw_text_rec(_description.wrapped, descriptionPos, width);
    }
