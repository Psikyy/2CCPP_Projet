#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Common.hpp"

class Plateau {
private:
    int nbJoueurs;                               
    int tailleGrille;                            
    std::vector<std::vector<char>> grille;               

public:

    Plateau(int nombreJoueurs, const std::vector<std::string>& nomsJoueurs);

    void afficherGrille() const;

    int getTailleGrille() const;
    int getNbJoueurs() const;
};

#endif 