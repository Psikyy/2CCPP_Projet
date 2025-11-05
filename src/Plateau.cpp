#include "../include/Plateau.hpp"

Plateau::Plateau(int nombreJoueurs, const std::vector<std::string>& nomsJoueurs)
    : nbJoueurs(nombreJoueurs), joueurs(nomsJoueurs)
{
    if (nbJoueurs < 2 || nbJoueurs > 9) {
        throw std::invalid_argument("Le nombre de joueurs doit être compris entre 2 et 9.");
    }

    tailleGrille = (nbJoueurs <= 4) ? 20 : 30;

    grille = std::vector<std::vector<char>>(tailleGrille, std::vector<char>(tailleGrille, '.'));
}

void Plateau::afficherGrille() const {
    for (int i = 0; i < tailleGrille; ++i) {
        for (int j = 0; j < tailleGrille; ++j) {
            std::cout << grille[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int Plateau::getTailleGrille() const { return tailleGrille; }
int Plateau::getNbJoueurs() const { return nbJoueurs; }
