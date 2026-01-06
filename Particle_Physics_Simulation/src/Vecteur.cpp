#include "../include/Vecteur.hpp"
#include <iostream>
#include <cmath>

using namespace std;

void Vecteur::afficheVecteur() const{
    cout << " ( " << m_x << "," << m_y << ")" << endl;
}

Vecteur& Vecteur::operator+=(Vecteur const& vec){
    m_x = m_x + vec.m_x;
    m_y = m_y + vec.m_y;
    return *this;
}

Vecteur operator+(Vecteur const& vec1, Vecteur const& vec2){
    Vecteur copie(vec1);
    copie += vec2;
    return copie;
}

Vecteur& Vecteur::operator-=(Vecteur const& vec){
    m_x = m_x - vec.m_x;
    m_y = m_y - vec.m_y;
    return *this;
}

Vecteur operator-(Vecteur const& vec1, Vecteur const& vec2){
    Vecteur copie(vec1);
    copie -= vec2;
    return copie;
}

Vecteur& Vecteur::operator*=(double scalaire){
    m_x = scalaire * m_x;
    m_y = scalaire * m_y;
    return *this;
}

Vecteur operator*(double scalaire, Vecteur vec){
    Vecteur copie(vec);
    copie *= scalaire;
    return copie;   
}

Vecteur& Vecteur::operator/=(double scalaire){
    m_x = m_x / scalaire;
    m_y = m_y / scalaire;
    return *this;
}

// Vecteur operator/(double scalaire, Vecteur vec){
//     Vecteur copie(vec);
//     copie /= scalaire;
//     return copie; 
// }

double Vecteur::operator*(Vecteur const& vec){
    return m_x*vec.m_x + m_y*vec.m_y;
}

double Vecteur::norme() const{
    return sqrt(m_x*m_x + m_y*m_y);
}


