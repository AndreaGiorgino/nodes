#include "lexer.hxx"

namespace fs = std::filesystem;

lexer::lexer_error::lexer_error(std::string_view message) noexcept {
    _message += message;
}

auto lexer::lexer_error::what(void) const noexcept -> const char* {
    return _message.c_str();
}

lexer::lexer(fs::path filePath)
    : _filePath(std::move(filePath)) {}

auto lexer::lexer::nodes(void) const -> std::generator<node> {
    // TODO: lexer::nodes method not implemented yet
    throw lexer::lexer_error("lexer::nodes method not implemented yet.");
}
