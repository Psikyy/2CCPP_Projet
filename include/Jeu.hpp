#ifndef JEU_HPP
#define JEU_HPP

#include <vector>
#include <string>
#include "Plateau.hpp"
#include "Joueur.hpp"
#include "Tuile.hpp"

class Jeu {
private:
    Plateau plateau;
    std::vector<Joueur> joueurs;
    std::vector<Tuile> pileTuiles; 
    size_t indexPile; 
    int toursParJoueur; 

public:
    Jeu(const std::vector<std::string>& noms, int tours = 9);

    void bouclePrincipale();

private:
    void initialiserTuiles();
    Tuile tirerPremiere();
    bool choisirParmiSuivantes(int choixRelatif, Tuile& sortie);
    void afficherOptionsTuiles(size_t start, int count = 5);
};

#endif
