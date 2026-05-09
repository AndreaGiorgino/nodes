option(ENABLE_DARK_THEME "Enable dark theme" OFF)

if(ENABLE_DARK_THEME)
    add_compile_definitions(DARK_THEME)
endif()
