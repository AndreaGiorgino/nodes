#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class node final {
    public:
        node(void) noexcept;
        node(std::string_view title, std::string_view description = {}) noexcept;
        ~node(void) noexcept = default;

        template<class Self>
        auto& title(this Self&& self) noexcept {
            return std::forward_like<Self>(self._title);
        }

    public:
        auto update(void) noexcept -> void;
        auto render(void) const noexcept -> void;

    private:
        std::string _title {};
        std::string _description {};

        // TODO: list of tasks
};

using node_ptr = std::shared_ptr<node>;
using node_map = std::unordered_map<std::string, node_ptr>;
