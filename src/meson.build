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
