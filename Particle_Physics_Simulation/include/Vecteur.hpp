#ifndef VECTEUR_HPP
#define VECTEUR_HPP
#include <iostream>


class Vecteur{

    public:

    // Initialisation
    Vecteur(double x = 0, double y = 0) : m_x(x), m_y(y){}

    // Constructeur par copie 
    Vecteur(Vecteur const& autre): m_x(autre.m_x), m_y(autre.m_y){}

    // Opérateurs arithmétiques 

    // Addition 
    Vecteur& operator+=(Vecteur const& vec);
    
    // Soustraction 
    Vecteur& operator-=(Vecteur const& vec);

    // Multiplication par un scalaire
    Vecteur& operator*=(double scalaire);

    // Division par un scalaire
    Vecteur& operator/=(double scalaire);

    // Produit scalaire 
    double operator*(Vecteur const& vec);

    // Produit vectoriel
    Vecteur& operator^=(Vecteur const& vec);

    // Norme

    double norme() const;

    // Methodes utiles 

double getX() {return m_x;}
double getY() {return m_y;}

void setX(double x){m_x = x;}
void setY(double y){m_y = y;}

    // Pour effectuer les vérifications
    void afficheVecteur() const;

    protected:

    double m_x;
    double m_y;
};

    Vecteur operator+(Vecteur const& vec1, Vecteur const& vec2);
    Vecteur operator-(Vecteur const& vec1, Vecteur const& vec2);
    Vecteur operator*(double scalaire, Vecteur vec);
    // Vecteur operator/(double scalaire, Vecteur vec);
    Vecteur operator^(Vecteur const& vec1, Vecteur const& vec2);
    
#endif