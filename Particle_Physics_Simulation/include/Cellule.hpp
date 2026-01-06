#ifndef CELLULE_HPP
#define CELLULE_HPP


#include "Particule.hpp"
#include "Vecteur.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cmath>


class Cellule{

    public:

    // - Rajouter une particule dans la cellule
    void rajoutPart(Particule& particule);

    // - Changement de cellule pour la particule
    std::vector<Particule>::iterator changementCell(Particule& particule, Cellule& cellChange, std::vector<Particule>::iterator it);

    // // Garde les indices vecteur des cellules proches pour la particule (cf voisinage)
    // std::vector<int> keepCellule(Univers univ, Particule& particule);

    double distance(Particule& part);

    ~Cellule(){
        m_collPart.clear();
    }


    void setIndiceProche(std::vector<int> indiceProche){m_indiceProche = indiceProche;}

    int getI(){return m_i;}
    int getJ(){return m_j;}
    int getId(){return m_identiVecteur;}
    std::vector<int> getIndProche(){return m_indiceProche;}

    Vecteur& getCoord(){return m_coordonnees;}
    std::vector<Particule>& getColl(){return m_collPart;}

    void setI(int i){m_i = i;}
    void setJ(int j){m_j = j;}
    void setId(int ij){m_identiVecteur = ij;}

    protected:

    // Identificateur dans le vecteur maillage
    int m_identiVecteur; 

    // Position de la cellule dans l'espace :)
    int m_i;
    int m_j;
    
    // Particules dans la Cellule
    std::vector<Particule> m_collPart;
    
    // Savoir la coordonnée du centre de la cellule
    Vecteur m_coordonnees;
    
    // "Coordonnées" indice vecteur 1D des cellules proches :=)
    std::vector<int> m_indiceProche;


};

#endif