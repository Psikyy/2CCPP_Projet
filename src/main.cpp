#include <iostream>
#include "Jeu.hpp"

int main() {
    std::vector<std::string> noms = {"Alice", "Bob"};
    Jeu jeu(noms);
    jeu.bouclePrincipale();
    return 0;
}

