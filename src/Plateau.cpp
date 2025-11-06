#include "../include/Plateau.hpp"

Plateau::Plateau(int nombreJoueurs, const std::vector<std::string>& nomsJoueurs)
    : nbJoueurs(nombreJoueurs)
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

bool Plateau::estPositionValide(const Coordonnee& pos) const {
    return pos.ligne >= 0 && pos.ligne < tailleGrille &&
           pos.col >= 0 && pos.col < tailleGrille;
}

bool Plateau::placerTuile(const Tuile& tuile, const Coordonnee& pos, int idJoueur) {
    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;
        if (!estPositionValide({x, y}) || grille[x][y] != '.')
            return false;
    }

    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;
        grille[x][y] = '0' + idJoueur;
    }

    return true;
}


int Plateau::getTailleGrille() const { return tailleGrille; }
int Plateau::getNbJoueurs() const { return nbJoueurs; }
