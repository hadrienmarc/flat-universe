#include "../src/Univers.cpp"

int main(){

    // Caractéristiques de l'espace! 
    double longueur; // définit selon l'abscisse
    double largeur; // définit selon l'ordonnées
    double rCut; // définit d'après l'énoncé
    double m;

    // Caractéstique associé à l'espace
    double eps;
    double sig;

    cout << "Rentrer la largeur souhaitée :" << endl;
    cin >> largeur;
    cout << "Rentrer la longueur souhaitée :" << endl;
    cin >> longueur;
    cout << "La distance à partir de laquelle le potentiel est négligé :" << endl;
    cout << "On a trouvé théoriquement la valeur qui est égale à 2" << endl;
    rCut = 2;
    cout << "Quel est l'epsilon choisi ? " << endl;
    cin >> eps;
    cout << "Et pour le sigma ? :" << endl;
    cin >> sig;

    double dt;
    double t_end;

    cout << "Rentrer t_end";
    cin >> t_end;
    cout << "Rentrer dt";
    cin >> dt;

    // Caractéristiques de l'espace
    double L1 = longueur;  // définit selon l'abscisse
    double L2 = largeur;  // définit selon l'ordonnées
    // Nombre de particules dans le carré rouge et le rectangle bleu
    int N1 = 1600;
    int N2 = 6400;
    
    // On s'aide du graphique obtenu : 
    
    // Distance qu'il y a entre les particules 
    double distance = 2.0 * pow(2.0, 1.0 / 6.0) * sig;
   
    // Initialisation d'un vecteur de particules
    std::vector<Particule> particules;
   
    // Ajout des particules du carré rouge
    double x = L1 / 4.0;
    double y = L2 / 4.0;
    for(int i = 0; i < N1; i++){
        particules.emplace_back(Particule(x, y, 0.0, 10.0, m));
        y += distance;
        if(y >= L2 / 2.0){
            y = L2 / 4.0;
            x += distance;
        }
    }
    // Ajout des particules du rectangle bleu
    x = L1 / 2.0 + L1 / 8.0;
    y = L2 / 8.0;
    for(int i = 0; i < N2; i++){
        particules.emplace_back(Particule(x, y, 0.0, 10.0, m));
        y += distance;
        if(y >= L2 * 7.0 / 8.0){
            y = L2 / 8.0;
            x += distance;
        }
    }
    

    Univers univ(longueur, largeur, rCut, eps, sig);
    // cout << univ.getNCLarg() << endl;
    // cout << univ.getNCLong();
    univ.initialisationParticules(particules);
    univ.simulation(t_end, dt);
    particules.clear();
}