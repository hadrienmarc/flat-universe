#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include "Vecteur.hpp"

#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cmath>

class Particule{

    public:
    
    Particule() : m_position(Vecteur()), m_vitesse(Vecteur()), m_masse(0), m_force(Vecteur()), m_oldForce(Vecteur()){}
    Particule(double x, double y, double v_x, double v_y, double masse) : m_position(x, y), m_vitesse(v_x, v_y), m_masse(masse), m_force(Vecteur()), m_oldForce(Vecteur()){}

    // // - Renvoie la distance entre la particule et une cellule
    // double distance(Cellule& cell);

    // // - Renvoie la Cellule où se trouve la particule(d'après ses coordonnées)
    // Cellule& ouEst(Univers& univ);


    Vecteur distance(Particule& part);
    Vecteur calcule_force_partielle(Particule& part, double eps, double sig, double rcut);
    Vecteur calcule_force_totale(std::vector<Particule>& collect, double eps, double sig, double rcut);
    


    //



    //vérifier si on laisse une référence ou non!
    Vecteur getPosition(){return m_position;}
    Vecteur getVitesse(){return m_vitesse;}
    double getMasse(){return m_masse;}
    Vecteur& getForce(){return m_force;}
    Vecteur& getOldForce(){return m_oldForce;}

    void setPosition(double x, double y){m_position.setX(x); m_position.setY(y);}
    void setVitesse(double v_x, double v_y){m_vitesse.setX(v_x); m_vitesse.setY(v_y);} 
    protected:

    Vecteur m_position;
    Vecteur m_vitesse;
    double m_masse;
    Vecteur m_force; 
    Vecteur m_oldForce;
};

#endif