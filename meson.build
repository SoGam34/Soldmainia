project(
    'Soldmania',
    'cpp',
    version: '0.1',
    default_options: [
        'warning_level=3',
        'cpp_std=c++14',
        'b_coverage=true',
        'werror=false',
    ],
)
##########################################################################
#                           PROGRAM FILES                                 #
##########################################################################
programm_files = files(
		   'Data/Data.cpp',
		   'Gebaude/Batilion_Ausbildungszentrum.cpp',
		   'Gebaude/Erholungsresort.cpp',
		   'Gebaude/Gebaeude.cpp',
		   'Gebaude/Traningszentrum.cpp',
		   'Gebaude/Scoutbüro.cpp',
		   'Gebaude/Zentrale.cpp',
		   'Rendern/View.cpp',
           'main.cpp',
           'Game.cpp',
           'Einheit.cpp',
           'Rendern/Auswahl.cpp',
           'Timer.cpp')

executable('Soldmania',
		   sources,
           install : true, 
           cpp_pch : 'pch/cpp_pch.h')

##########################################################################
#                           DEPENDENCIES                                 #
##########################################################################
deb_test = dependency('catch2-with-main')
deb_cli = dependency('cxxopts')
deb_logs = dependency('spdlog')

##########################################################################
#                         EXECUTEBLES                                    #
##########################################################################
build_target(
    'debug',
    programm_files,
    dependencies: [deb_cli, deb_logs],
    install: true,
cpp_pch : 'pch/cpp_pch.h'
    target_type: 'executable',
    override_options: [
        'buildtype=debug',
        'werror=false',
        'b_coverage=true',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
)

build_target(
    'release',
    programm_files,
    dependencies: [deb_cli, deb_logs],
    install: true,
cpp_pch : 'pch/cpp_pch.h'
    target_type: 'executable',
    override_options: [
        'buildtype=release',
        'werror=true',
        'b_coverage=false',
        'b_sanitize=none',  #['address', 'thread', 'undefined', 'memory', 'leak', 'address,undefined'],
    ],
)

##########################################################################
#                           DOXYGEN                                      #
##########################################################################
doxygen = find_program('doxygen', required: false)
if doxygen.found()
    message('Doxygen found')

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
    warning('Documentation disabled without doxygen')
endif

##########################################################################
#                           TESTS                                      #
##########################################################################

test_files = ['test1.cpp', 'test2.cpp']
test_sanitizer = ['address', 'thread', 'undefined', 'leak', 'address,undefined']  # 'memory',

foreach test : test_files
    foreach sanitizer : test_sanitizer
        test_exe = build_target(
            'TSuit:' + test + ' with ' + sanitizer,
            'tests/' + test,
            dependencies: deb_test,
            install: true,
            target_type: 'executable',
cpp_pch : 'pch/cpp_pch.h'
            override_options: [
                'buildtype=debug',
                'werror=false',
                'b_coverage=true',
                'b_sanitize=' + sanitizer,
            ],
        )
        test('Testsuit in ' + test, test_exe)
    endforeach
endforeach
