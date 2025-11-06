#include "../include/Jeu.hpp"
#include <iostream>

Jeu::Jeu(const std::vector<std::string>& noms)
    : plateau(noms.size(), noms), joueurActuel(0)
{
    for (int i = 0; i < (int)noms.size(); ++i)
        joueurs.emplace_back(noms[i], "vert", i + 1);
}

void Jeu::tourDeJeu() {
    Joueur& j = joueurs[joueurActuel];
    std::cout << "\n--- Tour de " << j.getNom() << " ---\n";
    plateau.afficherGrille();

    std::cout << "Entrez ligne et colonne pour placer votre tuile (ex: 3 4) : ";
    int l, c;
    std::cin >> l >> c;

    Tuile tuile({{0, 0}});

    if (plateau.placerTuile(tuile, {l, c}, j.getId()))
        std::cout << "Tuile placée avec succès !\n";
    else
        std::cout << "❌ Position invalide !\n";

    joueurActuel = (joueurActuel + 1) % joueurs.size();
}

void Jeu::bouclePrincipale() {
    for (int i = 0; i < 10; ++i) { 
        tourDeJeu();
    }

    std::cout << "\nFin du jeu !\n";
}
