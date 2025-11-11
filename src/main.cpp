#include <iostream>
#include <vector>
#include "../include/Jeu.hpp"

int main() {
    try {
        std::cout << "=== Laying Grass — mode console ===\n\n";

        int nbJoueurs = 2;
        std::cout << "Combien de joueurs ? (2-9) [default 2]: ";
        std::string s;
        std::getline(std::cin, s);
        if (!s.empty()) {
            try {
                int v = std::stoi(s);
                if (v >= 2 && v <= 9) nbJoueurs = v;
            } catch(...) {}
        }

        std::vector<std::string> noms;
        for (int i = 0; i < nbJoueurs; ++i) {
            std::string nom;
            std::cout << "Nom du joueur " << (i+1) << " : ";
            std::getline(std::cin, nom);
            if (nom.empty()) nom = std::string("J") + std::to_string(i+1);
            noms.push_back(nom);
        }

        Jeu jeu(noms, 9);
        jeu.bouclePrincipale();
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
