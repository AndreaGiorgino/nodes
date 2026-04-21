#include "node.hxx"

node::node(void)
    noexcept {
        // constructor
    }

node::node(std::string_view title, std::string_view description)
    noexcept :
    _title(std::string { title }),
    _description(std::string { description }) {
        // constructor
    }

auto node::update(void)
    noexcept -> void {
        // TODO: update node
    }

auto node::render(void)
    const noexcept -> void {
        // TODO: render node
    }
