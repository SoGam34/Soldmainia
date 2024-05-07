project('Soldmania', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])
  
sources = files(
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
           'Auswahl.cpp',
           'Timer.cpp')

executable('Soldmania',
		   sources,
           install : true, 
           cpp_pch : 'pch/cpp_pch.h')

#
#
#Test Abschnitt
#
#

#Seting up the BOOST Debendency 
testdep = dependency('boost', modules : ['unit_test_framework'])

#Erstellen des Ersten Tests
unitexe = executable('utf', 'test/unit_test.cpp', dependencies: testdep)
test('Boost UTF test', unitexe, timeout: 60)

unitexe = executable('test_timer', 'test/test_Timer.cpp', dependencies: testdep)
test('Timer Unit Test', unitexe, timeout: 60)
