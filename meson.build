project(
    'Soldmania',
    'cpp',
    version: '1.0.0',
    default_options: [
        'warning_level=3',
        'cpp_std=c++17',
        'b_coverage=true',
        'werror=false',
    ],
)
##########################################################################
#                           PROGRAM FILES                                 #
##########################################################################
# TODO: spliting up the source files in several list
programm_files_without_main = files(
    'src/Data/Data.cpp',
    'src/Data/Data.h',
    'src/Einheiten/Battelion.cpp',
    'src/Einheiten/Battelion.h',
    'src/Einheiten/Einheit.cpp',
    'src/Einheiten/Einheit.h',
    'src/Einheiten/Einheiten_CONST.h',
    'src/Einheiten/Einzelkampfer.cpp',
    'src/Einheiten/Einzelkampfer.h',
    'src/Einheiten/Gegenstand.cpp',
    'src/Einheiten/Gegenstand.h',
    'src/Einheiten/Ruestung.cpp',
    'src/Einheiten/Ruestung.h',
    'src/Einheiten/Waffen.cpp',
    'src/Einheiten/Waffen.h',
    'src/Game.cpp',
    'src/Game.h',
    'src/Gebaude/Batilion_Ausbildungszentrum.cpp',
    'src/Gebaude/Batilion_Ausbildungszentrum.h',
    'src/Gebaude/Erholungsresort.cpp',
    'src/Gebaude/Erholungsresort.h',
    'src/Gebaude/Gebaeude.cpp',
    'src/Gebaude/Gebaeude.h',
    'src/Gebaude/Scoutbuero.h',
    'src/Gebaude/Scoutbüro.cpp',
    'src/Gebaude/Traningszentrum.cpp',
    'src/Gebaude/Traningszentrum.h',
    'src/Gebaude/Zentrale.cpp',
    'src/Gebaude/Zentrale.h',
    'src/Rendern/Auswahl.cpp',
    'src/Rendern/Auswahl.h',
    'src/Rendern/View.cpp',
    'src/Rendern/View.h',
    'src/Timer.cpp',
    'src/Timer.h',
)

cli_files = files(
    'src/Rendern/cli/Cli.cpp',
    'src/Rendern/cli/Cli.h',
    'src/Rendern/cli/mainCli.cpp',
)
gui_files = files(
    'src/Rendern/gui/gui.cpp',
    'src/Rendern/gui/gui.h',
    'src/Rendern/gui/mainGui.cpp',
)
tui_files = files(
    'src/Rendern/tui/mainTui.cpp',
    'src/Rendern/tui/tui.cpp',
    'src/Rendern/tui/tui.h',
)

##########################################################################
#                           DEPENDENCIES                                 #
##########################################################################
deb_test = dependency('catch2-with-main')
deb_cli = dependency('cxxopts')
deb_logs = dependency('spdlog')
deb_config = dependency('nlohmann_json').as_system()

##########################################################################
#                         EXECUTEBLES                                    #
##########################################################################

#Cli Targets
build_target(
    'cDebug',
    [programm_files_without_main, cli_files],
    dependencies: [deb_cli, deb_logs, deb_config],
    install: true,
    target_type: 'executable',
    override_options: [
        'buildtype=debug',
        'werror=false',
        'b_coverage=true',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
    cpp_pch: 'pch/pre.h',
)

build_target(
    'cRelease',
    [programm_files_without_main, cli_files],
    dependencies: [deb_cli, deb_logs, deb_config],
    install: true,
    target_type: 'executable',
    override_options: [
        'buildtype=release',
        'werror=true',
        'b_coverage=false',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
    cpp_pch: 'pch/pre.h',
)

# Tui Targets
build_target(
    'tDebug',
    [programm_files_without_main, tui_files],
    dependencies: [deb_cli, deb_logs, deb_config],
    install: true,
    target_type: 'executable',
    override_options: [
        'buildtype=debug',
        'werror=false',
        'b_coverage=true',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
    cpp_pch: 'pch/pre.h',
)

build_target(
    'tRelease',
    [programm_files_without_main, tui_files],
    dependencies: [deb_cli, deb_logs, deb_config],
    install: true,
    target_type: 'executable',
    override_options: [
        'buildtype=release',
        'werror=true',
        'b_coverage=false',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
    cpp_pch: 'pch/pre.h',
)

# Gui Targets
build_target(
    'gDebug',
    [programm_files_without_main, gui_files],
    dependencies: [deb_cli, deb_logs, deb_config],
    install: true,
    target_type: 'executable',
    override_options: [
        'buildtype=debug',
        'werror=false',
        'b_coverage=true',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
    cpp_pch: 'pch/pre.h',
)

build_target(
    'gRelease',
    [programm_files_without_main, gui_files],
    dependencies: [deb_cli, deb_logs, deb_config],
    install: true,
    target_type: 'executable',
    override_options: [
        'buildtype=release',
        'werror=true',
        'b_coverage=false',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
    cpp_pch: 'pch/pre.h',
)

##########################################################################
#                           DOXYGEN                                      #
##########################################################################
doxygen = find_program('doxygen', required: false)
if doxygen.found()
    message('\n\nDoxygen found :) \n\n')

    cdata = configuration_data()
    cdata.set('VERSION', meson.project_version())
    cdata.set('PROJECT_NAME', meson.project_name())
    cdata.set('INPUT_DIR', meson.project_source_root() + '/src/')
    cdata.set('OUT_DIR', meson.project_source_root() + '/docs/')

    doxyfile = configure_file(
        input: 'doxyfile.in',
        output: 'doxyfile',
        configuration: cdata,
        install: false,
    )

    run_target('docs', command: [doxygen, doxyfile])
else
    warning('\n\nDocumentation disabled without doxygen :( \n\n')
endif

formater = find_program('clang-format', required: false)
if formater.found()
    message('\n\nClang-Format found :) \n\n')
    run_target(
        'format',
        command: [
            formater,
            '-i',
            programm_files_without_main,
            gui_files,
            tui_files,
            cli_files,
        ],
    )
else
    warning('\n\nFormating disabled without clang-format :( \n\n')
endif

tidy = find_program('clang-tidy', required: false)
if tidy.found()
    message('\n\nClang-Tidy found :) \n\n')
    run_target(
        'tidy',
        command: [
            tidy,
            '-p',
            'compile_commands.json',
            '--config-file=../.clang-tidy',
            programm_files_without_main,
            cli_files,
            gui_files,
            tui_files,
            files('pch/pre.h'),
        ],
    )
else
    warning('\n\nFormating disabled without clang-format\n\n')
endif

# TODO: running cppcheck and clang-tidy and the amount of warnings is not allowd to increase (splitline length)
# TODO: adding a fuzzer
# TODO: use cchache in the ci
#
##########################################################################
#                           TESTS                                      #
##########################################################################
# TODO: only use needed files
# TODO: abort if the test coverage is below 90%
#
test_files = [
    ['tests/t_timer.cpp', 'src/Timer.cpp'],
    [
        'tests/t_data.cpp',
        'src/Data/Data.cpp',
        'src/Einheiten/Einheit.cpp',
        'src/Einheiten/Battelion.cpp',
        'src/Einheiten/Einheit.cpp',
        'src/Einheiten/Einheiten_CONST.h',
        'src/Einheiten/Einzelkampfer.cpp',
        'src/Einheiten/Gegenstand.cpp',
        'src/Einheiten/Ruestung.cpp',
        'src/Einheiten/Waffen.cpp',
    ],
]
test_sanitizer = ['none']  #, 'address', 'undefined', 'leak', 'address,undefined'] # 'memory', 'thread'

foreach test : test_files
    foreach sanitizer : test_sanitizer
        suit = test[0].substring(6).split('.')[0]
        name = 'TSuit ' + suit + ' with ' + sanitizer
        test_exe = build_target(
            name,
            test,
            dependencies: [deb_test, deb_cli, deb_config, deb_logs],
            install: true,
            target_type: 'executable',
            override_options: [
                'buildtype=debug',
                'werror=false',
                'b_coverage=true',
                'b_sanitize=' + sanitizer,
            ],
            cpp_pch: 'pch/pre.h',
        )
        test(name, test_exe, suite: suit)
    endforeach
endforeach
