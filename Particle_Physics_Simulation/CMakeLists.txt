cmake_minimum_required(VERSION 3.0)
project(mon_projet)

# Inclure les dossiers 'include' et 'src'
include_directories(include)
add_subdirectory(src)

# Créer les exécutables de démonstration
add_subdirectory(demo)
