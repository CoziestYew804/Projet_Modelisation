cmake_minimum_required(VERSION 3.9)
project(ProjetSFML-Pacman)

set(CMAKE_CXX_STANDARD 11)

add_executable(Projet_Modelisation
        main.cpp
        Graphe/AElement.h Graphe/AElement.cpp Graphe/Arete.h Graphe/AStar.h Graphe/GElement.h Graphe/Graphe.h
        Graphe/InfoAlgo.h Graphe/InfoAlgo.cpp Graphe/PElement.h Graphe/Sommet.h Graphe/VSommet.h Graphe/VArete.h
        Graphe/OutilsCarte.h Graphe/OutilsCarte.cpp Graphe/VArete.cpp Graphe/VSommet.cpp

        Screen/FenetreGrapheSFML.h Screen/AlgebreLineaire.h
        Screen/Matrice22.h Screen/TransfoAffine2D.h Screen/Vecteur2D.h Screen/Reels.h

        World/board.h

        Erreur.h

        Screen/FenetreGrapheSFML.cpp Graphe/Algos.h
        GestionFichier/File.h
        Screen/Menu.h)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Projet_Modelisation ${SFML_LIBRARIES})
endif()