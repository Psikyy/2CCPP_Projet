// src/main.cpp
#include "../include/Jeu.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

int main() {
    std::cout << "=== Laying Grass — mode console (interactive) ===\n\n";

    int nb;
    while (true) {
        std::cout << "Nombre de joueurs ? (2-9) [default 2]: ";
        if (!(std::cin >> nb)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            nb = 2;
            break;
        }
        if (nb >= 2 && nb <= 9) break;
        std::cout << "Entrer un nombre entre 2 et 9.\n";
    }

    std::vector<std::string> noms;
    noms.reserve(nb);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 1; i <= nb; ++i) {
        std::string nom;
        std::cout << "Nom du joueur " << i << " : ";
        std::getline(std::cin, nom);
        if (nom.empty()) {
            nom = "Joueur" + std::to_string(i);
        }
        noms.push_back(nom);
    }

    int tours = 9;
    std::cout << "Nombre de tours par joueur ? (par défaut 9): ";
    if (!(std::cin >> tours) || tours <= 0) {
        tours = 9;
        std::cin.clear();
    }

    std::cout << "\nCréation de la partie pour " << nb << " joueur(s), " << tours << " tours chacun.\n\n";

    Jeu jeu(noms, tours);
    jeu.bouclePrincipale();

    std::cout << "\nMerci d'avoir joué — au revoir !\n";
    return 0;
}
