#include "../include/Plateau.hpp"

Plateau::Plateau(int nombreJoueurs, const std::vector<std::string>&)
    : nbJoueurs(nombreJoueurs)
{
    tailleGrille = (nbJoueurs <= 4) ? 20 : 30;
    grille = std::vector<std::vector<char>>(tailleGrille, std::vector<char>(tailleGrille, '.'));
}

std::string Plateau::couleurCase(char c) const {
    switch(c) {
        case '1': return "\033[31m1\033[0m";
        case '2': return "\033[34m2\033[0m";
        case '3': return "\033[32m3\033[0m";
        case '4': return "\033[33m4\033[0m";
        case '5': return "\033[35m5\033[0m";
        case '6': return "\033[36m6\033[0m";
        case '7': return "\033[97m7\033[0m";
        case '8': return "\033[37m8\033[0m";
        case '9': return "\033[38;5;208m9\033[0m";
    }
    return ".";
}

void Plateau::afficherGrille() const {
    std::cout << "   ";
    for (int col = 0; col < tailleGrille; ++col)
        std::cout << char('A' + col) << ' ';
    std::cout << "\n";

    for (int i = 0; i < tailleGrille; ++i) {
        std::cout << char('A' + i) << "  ";
        for (int j = 0; j < tailleGrille; ++j)
            std::cout << couleurCase(grille[i][j]) << ' ';
        std::cout << '\n';
    }
}

bool Plateau::estPositionValide(const Coordonnee& pos) const {
    return pos.ligne >= 0 && pos.ligne < tailleGrille &&
           pos.col >= 0 && pos.col < tailleGrille;
}

bool Plateau::placerTuile(const Tuile& tuile, const Coordonnee& pos, int idJoueur) {
    for (const auto& b : tuile.getForme()) {
        int x = pos.ligne + b.ligne;
        int y = pos.col + b.col;
        if (!estPositionValide({x,y}) || grille[x][y] != '.')
            return false;
    }
    for (const auto& b : tuile.getForme()) {
        int x = pos.ligne + b.ligne;
        int y = pos.col + b.col;
        grille[x][y] = '0' + idJoueur;
    }
    return true;
}

int Plateau::getTailleGrille() const { return tailleGrille; }
int Plateau::getNbJoueurs() const { return nbJoueurs; }
