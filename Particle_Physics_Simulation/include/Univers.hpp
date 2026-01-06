#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include "Cellule.hpp"
#include "Particule.hpp"
#include "Vecteur.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cmath>

/* On considére ici que m_maillage représente un vecteur 1D, on peut s'imaginer
à l'aide d'un crayon une grille, on utilise par la suite le coin en bas à gauche
comme étant l'origine à (0, 0) */


class Univers{

    public:

    Univers(double longueur = 0, double largeur = 0, double rcut = 0, double eps = 0, double sig = 0) : m_longueur(longueur), m_largeur(largeur), m_rCut(rcut), m_eps(eps), m_sig(sig){
        m_ncLong = m_longueur / m_rCut;
        m_ncLarg = m_largeur / m_rCut;
        m_maillage.resize(m_ncLarg*m_ncLong);
        initialisationCellules();
    }

    // - Permettra de vérifier et de changer si il le faut de la case du maillage correspondant
    void actualisationParticules();

    /* - Permet de donner selon des coordonnées l'indice correspondant dans
    la modélisation de notre problème cf vecteur 2D en 1D :)*/
    int tradCoordCellule(Vecteur coordonnees);

    // - Ecrit les indices des cellules proches 
    void procheCell(Cellule& cell);

    // - Initialise l'univers à l'aide de toutes les particules voulues
    void initialisationParticules(std::vector<Particule>& collParticules); 

    // - Initialise toutes les cellules de l'univers (voisins, coordonnées, identifiant, etc..)
    void initialisationCellules();

    // On calcule sur une particule, qui se trouve dans une cellule cell, 
    // les forces totales qui s'applique dessus :)
    void forceTot(Particule& particule, Cellule& cell);

    // Simulation du problème
    void simulation(double t_end, double dt);

    Cellule& ouEst(Particule& part);

    // Garde les indices vecteur des cellules proches pour la particule (cf voisinage)
    std::vector<int> keepCellule(Cellule& cell, Particule& particule);

    std::vector<Cellule>& getMaillage(){return m_maillage;}
    double getLong(){return m_longueur;}
    double getLarg(){return m_largeur;}
    double getR(){return m_rCut;}
    double getNCLong(){return m_ncLong;}
    double getNCLarg(){return m_ncLarg;}


    ~Univers(){
        m_maillage.clear();
    }


    protected:

    // Maillage du problème
    std::vector<Cellule> m_maillage; 

    // Caractéristiques de l'espace! 
    double m_longueur; // définit selon l'abscisse
    double m_largeur; // définit selon l'ordonnées
    double m_rCut;
    int m_ncLong;
    int m_ncLarg;

    // Caractéstique associé à l'espace
    double m_eps;
    double m_sig;

};

#endif