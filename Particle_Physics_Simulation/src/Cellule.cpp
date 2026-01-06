#include "../include/Cellule.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

// - Rajouter une particule dans la cellule
void Cellule::rajoutPart(Particule& particule){
    m_collPart.emplace_back(particule);
}



// - Changement de cellule pour la particule
vector<Particule>::iterator Cellule::changementCell(Particule& particule, Cellule& cellChange, vector<Particule>::iterator it){
    it = m_collPart.erase(it);
    cellChange.getColl().push_back(particule);
    return it;
}

// - Renvoie la distance entre la particule et une cellule
double Cellule::distance(Particule& part){
    return (part.getPosition() - m_coordonnees).norme();
}


// // Garde les indices vecteur des cellules proches pour la particule (cf voisinage)
// vector<int> Cellule::keepCellule(Univers univ, Particule& particule){
//     vector<int> indices;
//     double distance;
//     int nbCellProche = m_indiceProche.size();

//     for (int i = 0; i < nbCellProche; i++){
//         Cellule& cellProche = univ.getMaillage()[m_indiceProche[i]];
//         distance = particule.distance(cellProche);
//         if (distance < univ.getR()){
//             indices.push_back(m_indiceProche[i]);
//         }
//     }
//     return indices;
// }