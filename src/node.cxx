#include "enviroment.hxx"
#include "gui.hxx"
#include "node.hxx"
#include "raylib.h"
#include "raymath.h"
#include "uuid.hxx"

node::node(void)
    noexcept : _uuid(uuid::generate_v4()) {
        // empty
    }

node::node(std::string_view uuid, std::string_view title,
        std::string_view description, ::Vector2 pos)
    : _uuid(uuid), _pos(std::move(pos)) {
        if (uuid.empty())
            throw std::runtime_error(
                    "node error - cannot set the uuid to be empty");
        else if (!uuid::test_v4(uuid))
            throw std::runtime_error(
                    std::format(
                        "node error - invalid uuid v4 provided: {:?}", uuid));

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

auto node::update(void) noexcept -> void {
    // TODO: update node
}

auto node::render(void) const noexcept -> void {
    gui::draw_text_rec(_title.wrapped, _pos, width, padding,
            ::ColorAlpha(::BLUE, 0.2f));

    const auto titleSize = gui::measure_text(_title.wrapped);
    const ::Vector2 recPos {
        _pos.x,
        _pos.y + titleSize.y + padding * 2,
    };

    gui::draw_text_rec(_description.wrapped, recPos, width);
}

auto node::render_text(void) const noexcept -> void {
    const auto& env = enviroment::get_instance();
    const auto& camera = env.camera();

    auto textPos = ::GetWorldToScreen2D({
            _pos.x + padding * camera.zoom,
            _pos.y + padding * camera.zoom,
        }, camera);

    gui::draw_text(_title.wrapped, textPos);

    const auto titleSize = gui::measure_text(_title.wrapped);

    textPos = ::GetWorldToScreen2D({
            _pos.x + padding * camera.zoom,
            _pos.y + padding * camera.zoom * 3.0f + titleSize.y,
        }, camera);


    gui::draw_text(_description.wrapped, textPos);
}
