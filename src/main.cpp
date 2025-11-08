#include <iostream>
#include "../include/tuilesDef.hpp"
#include "../include/Tuile.hpp"
#include "../include/Plateau.hpp"

int main() {
    try {
        // --- Test du chargement des tuiles ---
        auto tuiles = chargerTuiles();
        std::cout << "Nombre de tuiles chargées : " << tuiles.size() << std::endl;


        Plateau plateau(2, {"Alice", "Bob"});
        std::cout << "\nPlateau créé avec " << plateau.getNbJoueurs()
                  << " joueurs, taille " << plateau.getTailleGrille() << "x"
                  << plateau.getTailleGrille() << std::endl;

        plateau.afficherGrille();

        std::cout << "\nAperçu de la première tuile :\n";
        tuiles[0].afficherApercu();

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


