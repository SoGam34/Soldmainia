project(
    'Soldmania',
    'cpp',
    version: '0.1',
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
programm_files_without_main = files(
    'src/Data/Data.cpp',
    'src/Einheit.cpp',
    'src/Game.cpp',
    'src/Gebaude/Batilion_Ausbildungszentrum.cpp',
    'src/Gebaude/Erholungsresort.cpp',
    'src/Gebaude/Gebaeude.cpp',
    'src/Gebaude/Scoutbüro.cpp',
    'src/Gebaude/Traningszentrum.cpp',
    'src/Gebaude/Zentrale.cpp',
    'src/Rendern/Auswahl.cpp',
    'src/Rendern/View.cpp',
    'src/Timer.cpp',

    )
    
main_file = files(
        'src/main.cpp',
)

##########################################################################
#                           DEPENDENCIES                                 #
##########################################################################
deb_test = dependency('catch2-with-main')
deb_cli = dependency('cxxopts')
deb_logs = dependency('spdlog')
deb_config = dependency('nlohmann_json')

##########################################################################
#                         EXECUTEBLES                                    #
##########################################################################
build_target(
    'debug',
[programm_files_without_main, main_file],
    dependencies: [deb_cli, deb_logs],
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
    'release',
[programm_files_without_main, main_file],
    dependencies: [deb_cli, deb_logs],
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
    message('\n\nDoxygen found\n\n')

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
    warning('\n\nDocumentation disabled without doxygen\n\n')
endif

##########################################################################
#                           TESTS                                      #
##########################################################################

test_files = ['test1.cpp', 'test2.cpp']
test_sanitizer = ['none', 'address', 'undefined', 'leak', 'address,undefined']  # 'memory', 'thread'

foreach test : test_files
    foreach sanitizer : test_sanitizer
        name = 'TSuit ' + test.split('.')[0] + ' with ' + sanitizer
        test_exe = build_target(
            name,
            ['tests/' + test, programm_files_without_main],
            dependencies: deb_test,
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
        test(name, test_exe, suite: test.split('.')[0])
    endforeach
endforeach
