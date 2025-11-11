#include "../include/Jeu.hpp"
#include <iostream>

int main() {
    std::vector<std::string> noms = {"Arthur", "Lucas"};
    Jeu jeu(noms, 5);

    Plateau &plateau = jeu.getPlateau();
    auto &pile = jeu.getPile();
    auto &joueurs = jeu.getJoueurs();

    std::cout << "\n=== TEST AUTOMATIQUE DEMARRE ===\n";

    plateau.placerTuile(Tuile({{0,0}}), {10,10}, 1);
    plateau.placerTuile(Tuile({{0,0}}), {10,12}, 2);

    for (int tour = 1; tour <= jeu.getNbTours(); ++tour) {
        std::cout << "\n--- TOUR " << tour << " ---\n";

        for (int pid = 1; pid <= (int)joueurs.size(); ++pid) {
            Joueur &j = joueurs[pid-1];
            if (pile.empty()) break;

            Tuile t = pile.front();
            pile.pop_front();
            if (tour % 2 == 0) t.rotate();
            if (tour % 3 == 0) t.flip();

            bool placed = false;
            for (int r = 8; r < 13 && !placed; r++) {
                for (int c = 8; c < 15 && !placed; c++) {
                    if (plateau.placerTuile(t, {r,c}, pid)) {
                        std::cout << j.getNom() << " place une tuile en " 
                                  << char('A'+c) << (r+1) << "\n";
                        placed = true;
                    }
                }
            }

            if (!placed) {
                std::cout << j.getNom() << " ne peut pas jouer → tuile défaussée.\n";
            }
        }

        plateau.afficherGrille();
    }

    std::cout << "\n===== FIN DU TEST AUTOMATIQUE =====\n";
    plateau.afficherGrille();
    std::cout << "\nCalcul des scores...\n";

    int nb = joueurs.size();
    std::vector<int> bestSquares(nb+1), totalCases(nb+1);

    for (int i = 1; i <= nb; i++) {
        bestSquares[i] = plateau.plusGrandCarrePour(i);
        totalCases[i] = plateau.nombreCasesPour(i);
        std::cout << joueurs[i-1].getNom()
                  << ": plus grand carre = " << bestSquares[i]
                  << " => " << (bestSquares[i] * bestSquares[i]) << " cases, total = "
                  << totalCases[i] << "\n";
    }

    int winner = 1;
    for (int i = 2; i <= nb; i++) {
        if (bestSquares[i] > bestSquares[winner]) winner = i;
        else if (bestSquares[i] == bestSquares[winner] && totalCases[i] > totalCases[winner])
            winner = i;
    }

    std::cout << "\nVainqueur automatique : " << joueurs[winner-1].getNom() << " !\n";

    return 0;
}
