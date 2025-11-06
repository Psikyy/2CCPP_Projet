#include <iostream>
#include "../include/Plateau.hpp"
#include <vector>
#include <string>

int main() {
    try {
        std::cout << "=== Test du Plateau ===" << std::endl;

        std::vector<std::string> noms = {"Alice", "Bob"};

        Plateau plateau(noms.size(), noms);

        std::cout << "Plateau créé avec " << plateau.getNbJoueurs()
                  << " joueurs sur une grille de taille "
                  << plateau.getTailleGrille() << "x"
                  << plateau.getTailleGrille() << std::endl;

        std::cout << "\nAffichage de la grille :\n";
        plateau.afficherGrille();

        std::cout << "\n=== Fin du test ===" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
