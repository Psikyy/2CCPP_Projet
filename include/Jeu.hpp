#ifndef JEU_HPP
#define JEU_HPP

#include <vector>
#include <string>
#include <deque>
#include "Plateau.hpp"
#include "Joueur.hpp"
#include "Tuile.hpp"

class Jeu {
private:
    Plateau plateau;
    std::vector<Joueur> joueurs;
    std::deque<Tuile> pileTuiles;
    int toursParJoueur;

public:
    Jeu(const std::vector<std::string>& noms, int tours = 9);
    void bouclePrincipale();

    Plateau& getPlateau() { return plateau; }
    std::deque<Tuile>& getPile() { return pileTuiles; }
    std::vector<Joueur>& getJoueurs() { return joueurs; }
    int getNbTours() const { return toursParJoueur; }

private:
    void initialiserTuiles();
    Tuile tirerPremiere();
    bool choisirParmiSuivantes(int choixRelatif, Tuile& sortie);
    void afficherOptionsTuiles(int count = 5);
};
#endif
