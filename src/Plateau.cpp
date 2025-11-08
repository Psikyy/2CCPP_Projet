#include "../include/Plateau.hpp"
#include <map>

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
    std::cout << "   ";
    for (int j = 0; j < tailleGrille; ++j) {
        if (j < 10) std::cout << j << "  ";
        else std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < tailleGrille; ++i) {
        if (i < 10) std::cout << i << "  ";
        else std::cout << i << " ";
        for (int j = 0; j < tailleGrille; ++j) {
            char c = grille[i][j];
            if (c == '.') {
                std::cout << ".  ";
            } else {
                int id = (c - 'A') + 1;
                static const std::vector<std::string> ansi = {
                    "\033[32m", 
                    "\033[34m", 
                    "\033[33m", 
                    "\033[35m", 
                    "\033[36m", 
                    "\033[31m", 
                    "\033[37m", 
                    "\033[90m", 
                    "\033[91m"  
                };
                std::string code = ansi[(id-1) % ansi.size()];
                std::cout << code << c << "\033[0m" << "  ";
            }
        }
        std::cout << '\n';
    }
}

bool Plateau::estPositionValide(const Coordonnee& pos) const {
    return pos.ligne >= 0 && pos.ligne < tailleGrille &&
           pos.col >= 0 && pos.col < tailleGrille;
}

bool Plateau::empieteSurAutre(int idJoueur, const Tuile& tuile, const Coordonnee& pos) const {
    char symboleJoueur = 'A' + (idJoueur - 1);
    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;

        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && ny >= 0 && nx < tailleGrille && ny < tailleGrille) {
                char other = grille[nx][ny];
                if (other != '.' && other != symboleJoueur) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Plateau::toucheTerritoireParCote(int idJoueur, const Tuile& tuile, const Coordonnee& pos) const {
    char symboleJoueur = 'A' + (idJoueur - 1);
    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;

        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && ny >= 0 && nx < tailleGrille && ny < tailleGrille) {
                if (grille[nx][ny] == symboleJoueur) return true;
            }
        }
    }
    return false;
}

bool Plateau::placerTuile(const Tuile& tuile, const Coordonnee& pos, int idJoueur) {
    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;
        if (!estPositionValide({x, y}) || grille[x][y] != '.') {
            return false;
        }
    }

    if (empieteSurAutre(idJoueur, tuile, pos)) {
        return false;
    }

    char symboleJoueur = 'A' + (idJoueur - 1);
    bool joueurADejaCases = false;
    for (int i = 0; i < tailleGrille && !joueurADejaCases; ++i)
        for (int j = 0; j < tailleGrille; ++j)
            if (grille[i][j] == symboleJoueur) { joueurADejaCases = true; break; }

    if (joueurADejaCases) {
        if (!toucheTerritoireParCote(idJoueur, tuile, pos)) {
            return false;
        }
    }

    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;
        grille[x][y] = symboleJoueur;
    }

    return true;
}

int Plateau::getTailleGrille() const { return tailleGrille; }
int Plateau::getNbJoueurs() const { return nbJoueurs; }

