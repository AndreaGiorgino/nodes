#include <format>
#include <fstream>

#include "parser.hxx"

namespace fs = std::filesystem;

parser::parser(fs::path filePath)
    : _filePath(std::move(filePath)) {
        if (!fs::exists(_filePath))
            throw std::runtime_error(
                    std::format(
                        "parser error - cannot find file: [{}]",
                        _filePath.string()));
        else if (!fs::is_regular_file(_filePath))
            throw std::runtime_error(
                    std::format(
                        "parser error - cannot read non-regular file: [{}]",
                        _filePath.string()));
    }

auto parser::words(void) const -> std::generator<word> {
    std::ifstream ifs(_filePath.string());
    if (!ifs) throw std::runtime_error(
            std::format(
                "parser error - cannot open file: [{}]",
                _filePath.string()));

    parser::word ret;
    while (!ifs.eof()) {
        // update the indentation level
        if (ret.col == 0) {
            while (!ifs.eof()
                    && (char)(unsigned)ifs.peek() == ' ') {
                ifs.get();
                ret.col++;
                ret.indentLevel++;
            };
        }

        const char ch = (unsigned)ifs.get();
        if (ch == '#') { // comments
            std::string line {};
            std::getline(ifs, line);
            continue;
        } else if (ch == '\n') {
            ret.row++;
            ret.col = 0;
            ret.indentLevel = 0;
            continue;
        } else if (std::isspace(ch)) {
            // TODO: co_yield
        } else ret.text += ch;
    };
}
