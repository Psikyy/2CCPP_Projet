#include "../include/Jeu.hpp"
#include "../include/tuilesDef.hpp"
#include <algorithm>
#include <random>
#include <iostream>
#include <limits>

Jeu::Jeu(const std::vector<std::string>& noms, int tours)
    : plateau((int)noms.size(), noms), indexPile(0), toursParJoueur(tours)
{
    for (int i = 0; i < (int)noms.size(); ++i) {
        std::string couleur = "color"; 
        joueurs.emplace_back(noms[i], couleur, i + 1);
    }

    initialiserTuiles();
}

void Jeu::initialiserTuiles() {
    pileTuiles = chargerTuiles();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pileTuiles.begin(), pileTuiles.end(), g);
    indexPile = 0;
}

Tuile Jeu::tirerPremiere() {
    if (indexPile >= pileTuiles.size()) {
        return Tuile();
    }
    Tuile t = pileTuiles[indexPile];
    pileTuiles.erase(pileTuiles.begin() + indexPile);
    return t;
}

bool Jeu::choisirParmiSuivantes(int choixRelatif, Tuile& sortie) {
    if (indexPile + choixRelatif >= (int)pileTuiles.size()) return false;
    size_t chosenIdx = indexPile + choixRelatif;
    sortie = pileTuiles[chosenIdx];

    std::vector<Tuile> prefix;
    for (size_t i = indexPile; i < chosenIdx; ++i) prefix.push_back(pileTuiles[i]);

    
    pileTuiles.erase(pileTuiles.begin() + indexPile, pileTuiles.begin() + chosenIdx + 1);

    for (auto& t : prefix) pileTuiles.push_back(t);

    return true;
}

void Jeu::afficherOptionsTuiles(size_t start, int count) {
    std::cout << "Tuiles disponibles (indices relatifs) :\n";
    for (int i = 0; i < count; ++i) {
        size_t idx = start + i;
        if (idx >= pileTuiles.size()) break;
        std::cout << i+1 << ") Aperçu tuile #" << idx+1 << " :\n";
        pileTuiles[idx].afficherApercu();
        std::cout << '\n';
    }
}

void Jeu::bouclePrincipale() {
    int nbJoueurs = (int)joueurs.size();

    std::cout << "Placement des tuiles de départ (1x1) pour chaque joueur.\n";
    for (int pid = 1; pid <= nbJoueurs; ++pid) {
        plateau.afficherGrille();
        std::cout << "Joueur " << joueurs[pid-1].getNom() << " (ID " << pid << "), place ta tuile de départ (1x1).\n";
        int l, c;
        while (true) {
            std::cout << "Entrez ligne et colonne (ex: 5 5) : ";
            if (!(std::cin >> l >> c)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            Tuile tuileDepart({{0,0}});
            if (plateau.placerTuile(tuileDepart, {l,c}, pid)) {
                std::cout << "Tuile de départ placée.\n";
                break;
            } else {
                std::cout << "Position invalide ou conflit. Réessaye.\n";
            }
        }
    }

    std::cout << "\nDébut de la partie : " << toursParJoueur << " tours par joueur.\n";

    for (int tour = 0; tour < toursParJoueur; ++tour) {
        for (int pid = 1; pid <= nbJoueurs; ++pid) {
            Plateau &p = plateau;
            Joueur &j = joueurs[pid-1];
            std::cout << "\n--- Tour " << (tour+1) << " / Joueur " << j.getNom() << " (ID " << pid << ") ---\n";
            p.afficherGrille();

            if (indexPile >= pileTuiles.size()) {
                std::cout << "Plus de tuiles en pile. Fin anticipée.\n";
                return;
            }

            Tuile tuileCourante = tirerPremiere();

            if (j.getCoupons() > 0 && indexPile < pileTuiles.size()) {
                std::cout << "Tu as " << j.getCoupons() << " coupon(s). Veux-tu choisir parmi les 5 tuiles suivantes ? (o/n) : ";
                char rep;
                std::cin >> rep;
                if (rep == 'o' || rep == 'O') {
                    size_t start = indexPile;
                    int maxOpt = 5;
                    if (start >= pileTuiles.size()) {
                        std::cout << "Aucune tuile suivante disponible.\n";
                    } else {
                        afficherOptionsTuiles(start, maxOpt);
                        std::cout << "Choisis 1.." << maxOpt << " (0 pour annuler) : ";
                        int choixRel;
                        std::cin >> choixRel;
                        if (choixRel >= 1 && choixRel <= maxOpt) {
                            if (choixRel - 1 < 0 || start + (choixRel-1) >= pileTuiles.size()) {
                                std::cout << "Choix invalide.\n";
                            } else {
                                if (j.utiliserCoupon()) {
                                    Tuile selection;
                                    bool ok = choisirParmiSuivantes(choixRel - 1, selection);
                                    if (ok) {
                                        tuileCourante = selection;
                                        std::cout << "Tu as choisi la tuile #" << (indexPile) << " (détails ci-dessous)\n";
                                        tuileCourante.afficherApercu();
                                    } else {
                                        std::cout << "Erreur lors du choix.\n";
                                    }
                                } else {
                                    std::cout << "Impossible d'utiliser le coupon (erreur).\n";
                                }
                            }
                        }
                    }
                }
            }

            std::cout << "Voulez-vous pivoter la tuile ? (nombre de rotations 90° cw, 0 = non) : ";
            int nbRot = 0; std::cin >> nbRot;
            for (int r = 0; r < nbRot; ++r) tuileCourante.rotate();

            std::cout << "Voulez-vous retourner la tuile horizontalement ? (o/n) : ";
            char rf; std::cin >> rf;
            if (rf == 'o' || rf == 'O') tuileCourante.flip();

            std::cout << "Aperçu de la tuile que tu vas poser :\n";
            tuileCourante.afficherApercu();

            int l, c;
            std::cout << "Entrez la ligne et la colonne pour placer la tuile (ex: 5 5) ou -1 -1 pour défausser : ";
            std::cin >> l >> c;
            if (l == -1 && c == -1) {
                std::cout << "Tuile défaussée.\n";
            } else {
                bool placed = plateau.placerTuile(tuileCourante, {l, c}, pid);
                if (placed) {
                    std::cout << "Tuile placée avec succès.\n";
                } else {
                    std::cout << "Placement invalide -> tuile défaussée.\n";
                }
            }

            std::cout << "Fin du tour de " << j.getNom() << ".\n";
        }
    }

    std::cout << "\n=== Fin des tours ===\n";
    plateau.afficherGrille();

    std::cout << "Note : le calcul final du plus grand carré n'est pas encore implémenté.\n";
}
