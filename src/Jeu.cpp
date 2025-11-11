#include "../include/Jeu.hpp"
#include "../include/tuilesDef.hpp"
#include <algorithm>
#include <random>
#include <iostream>
#include <limits>

Jeu::Jeu(const std::vector<std::string>& noms, int tours)
    : plateau((int)noms.size(), noms), toursParJoueur(tours)
{
    for (int i = 0; i < (int)noms.size(); ++i)
        joueurs.emplace_back(noms[i], "color", i + 1);
    initialiserTuiles();
}

void Jeu::initialiserTuiles() {
    std::vector<Tuile> tmp = chargerTuiles();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tmp.begin(), tmp.end(), g);
    pileTuiles.clear();
    for (auto &t : tmp) pileTuiles.push_back(t);
}

Tuile Jeu::tirerPremiere() {
    if (pileTuiles.empty()) return Tuile();
    Tuile t = pileTuiles.front();
    pileTuiles.pop_front();
    return t;
}

bool Jeu::choisirParmiSuivantes(int choixRelatif, Tuile& sortie) {
    if (choixRelatif < 0) return false;
    if ((size_t)choixRelatif >= pileTuiles.size()) return false;
    for (int i = 0; i < choixRelatif; ++i) {
        Tuile tmp = pileTuiles.front();
        pileTuiles.pop_front();
        pileTuiles.push_back(tmp);
    }
    sortie = pileTuiles.front();
    pileTuiles.pop_front();
    return true;
}

void Jeu::afficherOptionsTuiles(int count) {
    int displayed = 0;
    for (auto it = pileTuiles.begin(); it != pileTuiles.end() && displayed < count; ++it, ++displayed) {
        std::cout << "Option " << (displayed+1) << " :\n";
        it->afficherApercu();
    }
}

void Jeu::bouclePrincipale() {
    int nbJoueurs = (int)joueurs.size();
    for (int pid = 1; pid <= nbJoueurs; ++pid) {
        plateau.afficherGrille();
        std::cout << joueurs[pid-1].getNom() << ", place ta tuile de depart (1x1)\n";
        int l, c;
        while (true) {
            std::cout << "ligne colonne : ";
            if (!(std::cin >> l >> c)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            Tuile td({{0,0}});
            if (plateau.placerTuile(td, {l,c}, pid)) break;
            std::cout << "position invalide\n";
        }
    }

    for (int tour = 0; tour < toursParJoueur; ++tour) {
        for (int idx = 0; idx < nbJoueurs; ++idx) {
            int pid = idx + 1;
            Joueur &j = joueurs[idx];
            plateau.afficherGrille();
            if (pileTuiles.empty()) {
                std::cout << "pile vide\n";
                return;
            }

            Tuile tuileCourante = pileTuiles.front();
            std::cout << "\nTour " << (tour+1) << " - " << j.getNom() << " (id " << pid << ")\n";
            std::cout << "Tuile actuelle :\n";
            tuileCourante.afficherApercu();

            bool actionDone = false;

        while (!actionDone) {

            std::cout << "\n=== " << j.getNom() << " (Joueur " << pid << ") ===\n";
            std::cout << "Tuile actuelle:\n";
            tuileCourante.afficherApercu();

            std::cout << "\nCommandes :\n";
            std::cout << " R = Tourner    | F = Retourner\n";
            std::cout << " P = Poser      | N = Voir suivantes\n";
            std::cout << " E = Echanger   | S = Passer\n> ";

            char cmd;
            std::cin >> cmd;
            cmd = toupper(cmd);

            if (cmd == 'R') {
                tuileCourante.rotate();
            }
            else if (cmd == 'F') {
                tuileCourante.flip();
            }
            else if (cmd == 'N') {
                afficherOptionsTuiles(5);
            }
            else if (cmd == 'E') {
                if (j.getCoupons() <= 0) {
                    std::cout << "Pas de coupon.\n";
                    continue;
                }
                std::cout << "Choisir parmi les 5 suivantes (1-5), 0 annule :\n";
                afficherOptionsTuiles(5);
                int choix;
                std::cin >> choix;
                if (choix >= 1 && choix <= 5) {
                    if (choisirParmiSuivantes(choix-1, tuileCourante)) {
                        j.utiliserCoupon();
                    }
                }
            }
            else if (cmd == 'P') {
                std::string s;
                std::cout << "Case (ex: K10, X annule) : ";
                std::cin >> s;

                if (s == "X" || s == "x") continue;

                Coordonnee pos = plateau.convertirCase(s);

                if (plateau.placerTuile(tuileCourante, pos, pid)) {
                    pileTuiles.pop_front();
                    plateau.appliquerBonusesAprèsPlacement(pid, joueurs);
                    std::cout << "Placée.\n";
                    actionDone = true;
                } else {
                    std::cout << "Placement invalide.\n";
                }
            }
            else if (cmd == 'S') {
                std::cout << "Passe.\n";
                actionDone = true;
            }
            else {
                std::cout << "Commande inconnue.\n";
            }
        }
    }
}

    plateau.afficherGrille();
    std::cout << "\nFin des tours. Calcul des scores...\n";

    int nb = (int)joueurs.size();
    std::vector<int> bestSquares(nb+1,0);
    std::vector<int> totalCases(nb+1,0);
    for (int i=1;i<=nb;++i) {
        bestSquares[i] = plateau.plusGrandCarrePour(i);
        totalCases[i] = plateau.nombreCasesPour(i);
        std::cout << "Joueur " << joueurs[i-1].getNom() << " : plus grand carré = " << bestSquares[i]
                  << " (" << (bestSquares[i]*bestSquares[i]) << " cases), total cases = " << totalCases[i] << "\n";
    }

    int winner = 1;
    for (int i=2;i<=nb;++i) {
        if (bestSquares[i] > bestSquares[winner]) winner = i;
        else if (bestSquares[i] == bestSquares[winner] && totalCases[i] > totalCases[winner]) winner = i;
    }

    std::cout << "Vainqueur : " << joueurs[winner-1].getNom() << "\n";
}

