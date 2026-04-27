#include "enviroment.hxx"

namespace fs = std::filesystem;

auto enviroment::get_instance(void) noexcept -> enviroment& {
    static enviroment env;
    return env;
}

auto enviroment::init(std::string_view program) -> void {
    _program = fs::absolute(program);
    load_font();
}

auto enviroment::deinit(void) noexcept -> void {
    for (auto& [k, v] : _fontMap)
        ::UnloadFont(v);
    _fontMap.clear();
}

auto enviroment::load_font(unsigned fontSize) -> void {
    _fontSize = fontSize;

    if (_fontMap.contains(fontSize))
        return;

    const fs::path filePath {
        _program.parent_path() / "assets" / "fonts" / "default.ttf"
    };

    if (!fs::exists(filePath))
        throw std::runtime_error(
                std::format(
                    "enviroment error - cannot find font file: [{}]",
                    filePath.string()));

    _fontMap.insert({
                fontSize,
                ::LoadFontEx(filePath.c_str(), _fontSize, NULL, 0)
            });
}

auto enviroment::font(void) const -> std::pair<::Font, unsigned> {
    if (auto search = _fontMap.find(_fontSize);
            search != _fontMap.end())
        return std::make_pair(search->second, _fontSize);

    throw std::runtime_error(
            std::format("enviroment error - font size not loaded: {}",
                _fontSize));
}

auto enviroment::font_default(void) const -> std::pair<::Font, unsigned> {
    if (auto search = _fontMap.find(fontSizeDefault);
            search != _fontMap.end())
        return std::make_pair(search->second, fontSizeDefault);

    throw std::runtime_error("enviroment error - default font not loaded");
}
