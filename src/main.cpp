#include "../include/Jeu.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

int main() {
    std::cout << "=====================================\n";
    std::cout << "   🤖 LAYING GRASS - AUTO DEMO 🌿    \n";
    std::cout << "=====================================\n\n";

    std::vector<std::string> noms = {"Arthur", "Lucas"};
    Jeu jeu(noms, 9);

    auto& plateau = jeu.getPlateau();
    auto& joueurs = jeu.getJoueurs();

    std::cout << "🎮 Simulation automatique avec " << joueurs.size() << " joueurs.\n";
    std::cout << "Plateau " << plateau.getTailleGrille() << "x" << plateau.getTailleGrille() << "\n\n";

    std::vector<Coordonnee> starts = {
        {plateau.getTailleGrille() / 2, plateau.getTailleGrille() / 3},
        {plateau.getTailleGrille() / 2, 2 * plateau.getTailleGrille() / 3}
    };

    for (int i = 0; i < (int)joueurs.size(); ++i) {
        Tuile t({{0,0}});
        plateau.placerTuile(t, starts[i], joueurs[i].getId());
        joueurs[i].setTuileDepart(starts[i]);
    }

    plateau.afficherGrille();
    std::cout << "\n🌱 Tuiles de départ placées !\n\n";

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> rot(0, 3);
    std::uniform_int_distribution<int> flip(0, 1);
    std::uniform_int_distribution<int> pos(0, plateau.getTailleGrille()-1);

    auto& pile = jeu.getPile();

    for (int tour = 1; tour <= jeu.getNbTours(); ++tour) {
        std::cout << "\n--- 🌀 TOUR " << tour << " ---\n";
        for (auto& j : joueurs) {
            if (pile.empty()) break;
            Tuile t = pile.front();
            pile.pop_front();

            for (int r = 0; r < rot(rng); ++r) t.rotate();
            if (flip(rng)) t.flip();

            bool placé = false;
            for (int tries = 0; tries < 50 && !placé; ++tries) {
                int r = pos(rng);
                int c = pos(rng);
                Coordonnee p{r,c};
                if (plateau.placerTuile(t, p, j.getId())) {
                    std::cout << j.getNom() << " place une tuile en "
                              << char('A'+c) << (r+1) << "\n";
                    plateau.appliquerBonusesAprèsPlacement(j.getId(), joueurs);
                    placé = true;
                }
            }

            if (!placé)
                std::cout << j.getNom() << " ne peut pas jouer → tuile défaussée.\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }

        plateau.afficherGrille();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\n===== 🏁 FIN DE LA PARTIE =====\n";
    plateau.afficherGrille();

    std::cout << "\nCalcul des scores...\n";
    int bestId = 1;
    int bestCarre = 0, bestCases = 0;

    for (auto& j : joueurs) {
        int c = plateau.plusGrandCarrePour(j.getId());
        int n = plateau.nombreCasesPour(j.getId());
        std::cout << j.getNom() << " : carré = " << c << " (" << c*c
                  << " cases), total = " << n << "\n";

        if (c > bestCarre || (c == bestCarre && n > bestCases)) {
            bestCarre = c;
            bestCases = n;
            bestId = j.getId();
        }
    }

    std::cout << "\n🏆 Vainqueur automatique : " << joueurs[bestId-1].getNom()
              << " !\n";

    std::cout << "\n🌿 Démo terminée. Merci d’avoir regardé ! 🌿\n";
    return 0;
}
