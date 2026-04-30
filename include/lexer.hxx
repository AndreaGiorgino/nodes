#pragma once
#include <filesystem>
#include <generator>

#include "node.hxx"

class lexer final {
    public:
        class lexer_error final : public std::exception {
            public:
                lexer_error(std::string_view message = "Unknown error.") noexcept;

            public:
                auto what(void) const noexcept -> const char* override;

            private:
                std::string _message { "lexer error - " };
        };

    public:
        lexer(std::filesystem::path filePath);
        lexer(const lexer&) = delete;
        lexer(lexer&&) = delete;

    public:
        auto nodes(void) const -> std::generator<node>;

    private:
        std::filesystem::path _filePath {};
};
