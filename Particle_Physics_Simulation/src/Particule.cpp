#include "../include/Particule.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std; 


// // - Renvoie la distance entre la particule et une cellule
// double Particule::distance(Cellule& cell){
//     return (m_position - cell.getCoord()).norme();
// }

// // - Renvoie la Cellule où se trouve la particule(d'après ses coordonnées)
// Cellule& Particule::ouEst(Univers& univ){
//     double indice = univ.tradCoordCellule(m_position);
//     return univ.getMaillage()[indice];
// }




Vecteur Particule::distance(Particule& part){
    // Différence bien définie dans Vecteur.cpp
    return m_position - part.m_position;
}

Vecteur Particule::calcule_force_partielle(Particule& part, double eps, double sig, double rcut){
    /* Les opérateurs fait sur Vecteur vont bien nous servir par la suite
    pour une telle configuration */
    Vecteur rij = distance(part);
    double norme_rij = distance(part).norme();
    
    if (norme_rij < rcut){
        double puissance = (sig/norme_rij)*(sig/norme_rij);
        puissance = puissance * puissance * puissance;
        double fij = 24*eps*((puissance)/(norme_rij*norme_rij))*(1 - 2*puissance);
        Vecteur forceij = fij*rij;
        return forceij;
    }
    else{
        return Vecteur(0, 0);
    }
}

Vecteur Particule::calcule_force_totale(vector<Particule>& collect, double eps, double sig, double rcut){
    int taille = collect.size();
    Vecteur force_totale;
    for(int k = 0; k < taille; k++){
        // A verifier le == ici sur l'adresse
        if (this == &collect[k]){
            continue;
        }
        else{
            force_totale += calcule_force_partielle(collect[k], eps, sig, rcut);
        }
    }
    return 24 * eps * force_totale;
}

