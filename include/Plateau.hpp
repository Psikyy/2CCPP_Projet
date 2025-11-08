#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Common.hpp"
#include "Tuile.hpp"

class Plateau {
private:
    int nbJoueurs;
    int tailleGrille;
    std::vector<std::vector<char>> grille;
    std::string couleurCase(char c) const;

public:
    Plateau(int nombreJoueurs, const std::vector<std::string>& nomsJoueurs);

    void afficherGrille() const;

    int getTailleGrille() const;
    int getNbJoueurs() const;

    bool estPositionValide(const Coordonnee& pos) const;
    bool placerTuile(const Tuile& tuile, const Coordonnee& pos, int idJoueur);
};

#endif

