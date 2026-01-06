#include "../include/Univers.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cmath>


using namespace std;

// - Permettra de vérifier et de changer si il le faut de la case du maillage correspondant
void Univers::actualisationParticules() {
    for (vector<Cellule>::size_type i = 0; i < m_maillage.size(); i++) {
        vector<Particule>& collPart = m_maillage[i].getColl();
        for (auto it = collPart.begin(); it != collPart.end(); ) {
            Particule& part = *it;
            Cellule& cell = ouEst(part);
            if (cell.getId() != m_maillage[i].getId()) {
                it = m_maillage[i].changementCell(part, cell, it);
            } else {
                ++it;
            }
        }
    }
}

/* - Permet de donner selon des coordonnées l'indice correspondant correspondant dans
la modélisation de notre problème cf vecteur 2D en 1D :)*/

int Univers::tradCoordCellule(Vecteur coordonnees){
    int i(0);
    int j(0);
    int x = coordonnees.getX();
    int y = coordonnees.getY();
    while((i+1)*m_ncLong < x){
        i += 1;
    }
    while((j+1)*m_ncLarg < y){
        j += 1;
    }
    // cout << j*(m_ncLong) + i << endl;
    return j*(m_ncLong) + i;
    // int x = coordonnees.getX();
    // int y = coordonnees.getY();
    // // Selon la largeur
    // int i = y / m_ncLarg;
    // // Selon la longueur
    // int j = x / m_ncLong;
    // // cout << i*(m_ncLong) + j;
    // // Position dans le vecteur 1D : 
    // return i*(m_ncLong) + j;
}

// - Ecrit les indices des cellules proches 
void Univers::procheCell(Cellule& cell){
    int i = cell.getI();
    int j = cell.getJ();
    vector<int> indices_cellules;
    for (int k = -1; k <= 1; k++){
        for (int l = -1; l <= 1; l++){
            if (0 <= i + k && i+ k <= m_ncLarg && 0 <= j + l && j + l<= m_ncLong){
                indices_cellules.emplace_back(tradCoordCellule(Vecteur(j +l, i + k)));
            }
            else{
                continue;
            }
        }
    }
    cell.setIndiceProche(indices_cellules);
}


// - Initialise l'univers à l'aide de toutes les particules voulues
void Univers::initialisationParticules(vector<Particule>& collParticules){
    for (size_t i = 0; i < collParticules.size(); i++){
        Particule part = collParticules[i];
        // On récupère la cellule où se trouve 
        Cellule& cell = ouEst(part);
        cell.rajoutPart(part);
    }
}

// - Initialise toutes les cellules de l'univers
void Univers::initialisationCellules(){
    // Considère dans le constructeur qu'on a un vecteur de taille m_ncLarg x m_ncLong
    for (int i = 0; i < m_ncLarg; i++){
        for (int j = 0; j < m_ncLong; j++){
            Cellule& cell = m_maillage[i*m_ncLong + j];
            // Cellule proches
            procheCell(cell);
            // Set les coordonnées + identifiants vecteurs 
            cell.setI(i);
            cell.setJ(j);
            cell.setId(i*m_ncLong + j);
            cell.getCoord().setX((j+0.5)*m_ncLong);
            cell.getCoord().setY((i+0.5)*m_ncLarg);
        }
    }
}

// - Renvoie la Cellule où se trouve la particule(d'après ses coordonnées)
Cellule& Univers::ouEst(Particule& part){
    Vecteur coord = part.getPosition();
    double indice = tradCoordCellule(coord);
    
    if (indice >= 0 && indice < m_maillage.size()) {
        return m_maillage[indice];
    } 
    
    else {
        cout << "Problème d'indice";
    }
}


// On calcule sur une particule, qui se trouve dans une cellule cell, 
// les forces totales qui s'applique dessus :)
void Univers::forceTot(Particule& particule, Cellule& cell){
    vector<int> indices = keepCellule(cell, particule);
    Vecteur force;
    for (vector<int>::size_type i = 0; i < indices.size(); i++){
        Cellule& cellVoisine = m_maillage[indices[i]];
        force += particule.calcule_force_totale(cellVoisine.getColl(), m_eps, m_sig, m_rCut);
    }
    particule.getForce().setX(force.getX());
    particule.getForce().setY(force.getY()); 
}


// Garde les indices vecteur des cellules proches pour la particule (cf voisinage)
std::vector<int> Univers::keepCellule(Cellule& cell, Particule& particule){
    vector<int> indices;
    double distance;
    vector<int> indicesProches = cell.getIndProche();
    vector<int>::size_type nbCellProche = indicesProches.size();

    for (vector<int>::size_type i = 0; i < nbCellProche; i++){
        Cellule& cellProche = m_maillage[indicesProches[i]];
        distance = cellProche.distance(particule);
        if (distance < m_rCut){
            indices.emplace_back(indicesProches[i]);
        }
    }
    return indices;
}



// Simulation du problème
void Univers::simulation(double t_end, double dt){
    /* On suppose ici que l'on a déjà initialisé les particules  et les cellules
    avec les méthodes correspondantes */

    double t = 0.0;
    int taille_maillage = m_maillage.size();

    // Vecteur de temps :  
    vector<double> temps;
    temps.push_back(t);

    while (t < t_end){
        t += dt;
        temps.push_back(t);
        
        // Première boucle position : on s'occupe de chacune des cellules 
        for (int i_mail = 0; i_mail < taille_maillage; i_mail++){
            Cellule& cell = m_maillage[i_mail];
            // On récupère les particules de la cellule
            vector<Particule>& collecPart = cell.getColl();
            int nbParticules = collecPart.size();
            for (int i_part = 0; i_part < nbParticules; i_part++){
                Particule& part = collecPart[i_part];
                Vecteur force = part.getForce();
                double mi = part.getMasse();

                // Pour x
                double x_i = part.getPosition().getX();
                double v_xi = part.getVitesse().getX();
                double f_xi = force.getX();

                double new_xi = x_i + dt*(v_xi + 0.5*f_xi*dt/mi);

                // Pour y 
                double y_i = part.getPosition().getY();
                double v_yi = part.getVitesse().getY();
                double f_yi = force.getY();

                double new_yi = y_i + dt*(v_yi + 0.5*f_yi*dt/mi);

                // Mise à jour de la position
                part.setPosition(new_xi, new_yi);
                // Old Force = force
                part.getOldForce().setX(force.getX());
                part.getOldForce().setY(force.getY());
            }  
        }
        // On a fait la première boucle for sur toutes les particules

        // On actualise les cellules maintenant que les particules ont bougé
        actualisationParticules();

        // Calcul des foces est indépendant de la vitesse ==> on calcul force et boucle for ensemble
        for (int i_mail = 0; i_mail < taille_maillage; i_mail++){
            Cellule& cell = m_maillage[i_mail];
            // On récupère les particules de la cellule
            vector<Particule>& collecPart = cell.getColl();
            int nbParticules = collecPart.size();
            for (int i_part = 0; i_part < nbParticules; i_part++){
                Particule& part = collecPart[i_part];
                // Calcul des forces totales qui s'appliquent sur les particules
                forceTot(part, cell);

                double mi = part.getMasse();
                Vecteur force = part.getForce();
                Vecteur oldForce = part.getOldForce();

                // Pour x 
                double v_xi = part.getVitesse().getX();
                double f_xi = force.getX();
                double f_xi_old = oldForce.getX();

                double new_v_xi = v_xi + 0.5*dt*(f_xi_old + f_xi)/mi;

                // Pour y 
                double v_yi = part.getVitesse().getY();
                double f_yi = force.getY();
                double f_yi_old = oldForce.getY();

                double new_v_yi = v_yi + 0.5*dt*(f_yi_old + f_yi)/mi;

                // Mise à jour
                part.setVitesse(new_v_xi, new_v_yi);
            }  
        }
    }
}
