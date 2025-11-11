#include "../include/Plateau.hpp"
#include "../include/Joueur.hpp"
#include <queue>
#include <cmath>
#include <algorithm>

Plateau::Plateau(int nombreJoueurs, const std::vector<std::string>&)
    : nbJoueurs(nombreJoueurs)
{
    tailleGrille = (nbJoueurs <= 4) ? 20 : 30;
    grille = std::vector<std::vector<char>>(tailleGrille, std::vector<char>(tailleGrille, '.'));
    bonus = std::vector<std::vector<char>>(tailleGrille, std::vector<char>(tailleGrille, '.'));
    initialiserBonusesFixes();
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
    if (c == 'E') return "\033[32mE\033[0m";
    if (c == 'P') return "\033[90mP\033[0m";
    if (c == 'V') return "\033[35mV\033[0m";
    return ".";
}

void Plateau::afficherGrille() const {
    std::cout << "   ";
    for (int col = 0; col < tailleGrille; ++col) std::cout << char('A' + col) << ' ';
    std::cout << "\n";
    for (int i = 0; i < tailleGrille; ++i) {
        std::cout << char('A' + i) << "  ";
        for (int j = 0; j < tailleGrille; ++j) {
            char c = grille[i][j];
            if (c != '.') std::cout << couleurCase(c) << ' ';
            else if (bonus[i][j] != '.') std::cout << couleurCase(bonus[i][j]) << ' ';
            else std::cout << ". ";
        }
        std::cout << '\n';
    }
}

bool Plateau::estPositionValide(const Coordonnee& pos) const {
    return pos.ligne >= 0 && pos.ligne < tailleGrille &&
           pos.col >= 0 && pos.col < tailleGrille;
}

bool Plateau::empieteSurAutre(int idJoueur, const Tuile& tuile, const Coordonnee& pos) const {
    char symboleJoueur = '0' + idJoueur;
    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;
        const int dx[4] = {1,-1,0,0};
        const int dy[4] = {0,0,1,-1};
        for (int k=0;k<4;++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx>=0 && ny>=0 && nx<tailleGrille && ny<tailleGrille) {
                char other = grille[nx][ny];
                if (other != '.' && other != symboleJoueur) return true;
            }
        }
    }
    return false;
}

bool Plateau::toucheTerritoireParCote(int idJoueur, const Tuile& tuile, const Coordonnee& pos) const {
    char symboleJoueur = '0' + idJoueur;
    for (const auto& bloc : tuile.getForme()) {
        int x = pos.ligne + bloc.ligne;
        int y = pos.col + bloc.col;
        const int dx[4] = {1,-1,0,0};
        const int dy[4] = {0,0,1,-1};
        for (int k=0;k<4;++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx>=0 && ny>=0 && nx<tailleGrille && ny<tailleGrille) {
                if (grille[nx][ny] == symboleJoueur) return true;
            }
        }
    }
    return false;
}

bool Plateau::placerTuile(const Tuile& tuile, const Coordonnee& pos, int idJoueur) {
    for (const auto& b : tuile.getForme()) {
        int x = pos.ligne + b.ligne;
        int y = pos.col + b.col;
        if (!estPositionValide({x,y}) || grille[x][y] != '.') return false;
        if (bonus[x][y] == 'X') return false;
    }

    if (empieteSurAutre(idJoueur, tuile, pos)) return false;

    char symboleJoueur = '0' + idJoueur;
    bool joueurADejaCases = false;
    for (int i=0;i<tailleGrille && !joueurADejaCases;++i)
        for (int j=0;j<tailleGrille;++j)
            if (grille[i][j] == symboleJoueur) { joueurADejaCases = true; break; }

    if (joueurADejaCases) {
        if (!toucheTerritoireParCote(idJoueur, tuile, pos)) return false;
    }

    for (const auto& b : tuile.getForme()) {
        int x = pos.ligne + b.ligne;
        int y = pos.col + b.col;
        grille[x][y] = symboleJoueur;
    }

    return true;
}

bool Plateau::estCaseBonusValide(int r, int c) const {
    if (r<=0 || c<=0 || r>=tailleGrille-1 || c>=tailleGrille-1) return false;
    if (bonus[r][c] != '.') return false;
    return true;
}

void Plateau::initialiserBonusesFixes() {
    int nbEchange = (int)std::ceil(1.5 * nbJoueurs);
    int nbPierre = (int)std::ceil(0.5 * nbJoueurs);
    int nbVol = nbJoueurs;
    int placedE=0, placedP=0, placedV=0;
    int step = std::max(2, tailleGrille/6);
    for (int r = step; r < tailleGrille-step && (placedE<nbEchange || placedP<nbPierre || placedV<nbVol); r += step) {
        for (int c = step; c < tailleGrille-step && (placedE<nbEchange || placedP<nbPierre || placedV<nbVol); c += step) {
            if (!estCaseBonusValide(r,c)) continue;
            if (placedE < nbEchange) { bonus[r][c] = 'E'; ++placedE; continue; }
        }
    }
    for (int r = step/2; r < tailleGrille-step/2 && (placedP<nbPierre || placedV<nbVol); r += step) {
        for (int c = step/2; c < tailleGrille-step/2 && (placedP<nbPierre || placedV<nbVol); c += step) {
            if (!estCaseBonusValide(r,c)) continue;
            if (placedP < nbPierre) { bonus[r][c] = 'P'; ++placedP; continue; }
        }
    }
    for (int r = step; r < tailleGrille-step && placedV<nbVol; r += step) {
        for (int c = step/3; c < tailleGrille-step/3 && placedV<nbVol; c += step) {
            if (!estCaseBonusValide(r,c)) continue;
            bonus[r][c] = 'V';
            ++placedV;
            if (placedV>=nbVol) break;
        }
    }
}

void Plateau::appliquerBonusesAprèsPlacement(int idJoueur, std::vector<Joueur>& joueurs) {
    char sym = '0' + idJoueur;
    for (int r=1;r<tailleGrille-1;++r) {
        for (int c=1;c<tailleGrille-1;++c) {
            if (bonus[r][c]=='.') continue;
            const int dx[4] = {1,-1,0,0};
            const int dy[4] = {0,0,1,-1};
            bool entouré=false;
            entouré = true;
            for (int k=0;k<4;++k) {
                int nx=r+dx[k], ny=c+dy[k];
                if (nx<0 || ny<0 || nx>=tailleGrille || ny>=tailleGrille) { entouré=false; break; }
                if (grille[nx][ny] != sym) { entouré=false; break; }
            }
            if (!entouré) continue;
            char type = bonus[r][c];
            bonus[r][c] = '.';
            grille[r][c] = sym;
            Joueur &j = joueurs[idJoueur-1];
            if (type == 'E') {
                j.ajouterCoupon();
            } else if (type == 'P') {
                std::cout << "Joueur " << j.getNom() << " a gagné une case pierre. Choisis où la poser (ligne col) : ";
                int lr, lc;
                while (true) {
                    if (!(std::cin >> lr >> lc)) { std::cin.clear(); std::cin.ignore(10000,'\n'); continue; }
                    if (lr<0 || lc<0 || lr>=tailleGrille || lc>=tailleGrille) { std::cout << "Invalide\n"; continue; }
                    if (grille[lr][lc] != '.' || bonus[lr][lc] != '.') { std::cout << "Occupé\n"; continue; }
                    bonus[lr][lc] = 'X';
                    break;
                }
            } else if (type == 'V') {
                std::cout << "Joueur " << j.getNom() << " a gagné un bonus VOL. Choisis un joueur cible (id): ";
                int cibleId;
                std::cin >> cibleId;
                if (cibleId >= 1 && cibleId <= nbJoueurs && cibleId != idJoueur) {
                    std::cout << "Donne coordonées d'une case du joueur cible à voler (ligne col): ";
                    int lr, lc;
                    if (std::cin >> lr >> lc) {
                        if (lr>=0 && lc>=0 && lr<tailleGrille && lc<tailleGrille && grille[lr][lc] == char('0'+cibleId)) {
                            grille[lr][lc] = sym;
                        } else {
                            std::cout << "Coordonnées invalides ou case non du joueur cible\n";
                        }
                    }
                } else {
                    std::cout << "Cible invalide\n";
                }
            }
        }
    }
}

int Plateau::plusGrandCarrePour(int idJoueur) const {
    char sym = '0' + idJoueur;
    int n = tailleGrille;
    std::vector<std::vector<int>> dp(n, std::vector<int>(n,0));
    int best = 0;
    for (int i=0;i<n;++i) {
        for (int j=0;j<n;++j) {
            if (grille[i][j] == sym) {
                if (i==0 || j==0) dp[i][j]=1;
                else dp[i][j] = 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                if (dp[i][j] > best) best = dp[i][j];
            } else dp[i][j]=0;
        }
    }
    return best;
}

int Plateau::nombreCasesPour(int idJoueur) const {
    char sym = '0' + idJoueur;
    int count=0;
    for (int i=0;i<tailleGrille;++i)
        for (int j=0;j<tailleGrille;++j)
            if (grille[i][j]==sym) ++count;
    return count;
}

Coordonnee Plateau::convertirCase(const std::string& input) const {
    if (input.size() < 2) return {-1, -1};

    char colChar = toupper(input[0]);
    int col = colChar - 'A';

    int row;
    try {
        row = std::stoi(input.substr(1)) - 1;
    } catch (...) {
        return {-1, -1};
    }

    return {row, col};
}

int Plateau::getTailleGrille() const { return tailleGrille; }
int Plateau::getNbJoueurs() const { return nbJoueurs; }
