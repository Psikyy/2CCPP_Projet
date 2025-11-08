#include "../include/Jeu.hpp"
#include <iostream>

Jeu::Jeu(const std::vector<std::string>& noms)
    : plateau(noms.size(), noms), joueurActuel(0)
{
    for (int i = 0; i < (int)noms.size(); ++i)
        joueurs.emplace_back(noms[i], "vert", i + 1);

    tuilesDisponibles = chargerTuiles();
}

void Jeu::tourDeJeu() {
    Joueur& j = joueurs[joueurActuel];
    std::cout << "\n=== Tour de " << j.getNom() << " ===\n";
    plateau.afficherGrille();

    std::cout << "\nChoisissez une tuile (0-" << tuilesDisponibles.size() - 1 << ") : ";
    int choix;
    std::cin >> choix;

    if (choix < 0 || choix >= (int)tuilesDisponibles.size()) {
        std::cout << "❌ Numéro de tuile invalide !" << std::endl;
        return;
    }

    Tuile t = tuilesDisponibles[choix];

    std::cout << "Rotation ? (0 = non, 1 = oui) : ";
    int r; std::cin >> r;
    if (r == 1) t.rotate();

    std::cout << "Flip ? (0 = non, 1 = oui) : ";
    int f; std::cin >> f;
    if (f == 1) t.flip();

    std::cout << "\nAperçu de la tuile choisie :\n";
    t.afficherApercu();

    std::cout << "Entrez la ligne et la colonne de placement (ex: 3 4) : ";
    int l, c;
    std::cin >> l >> c;

    if (plateau.placerTuile(t, {l, c}, j.getId()))
        std::cout << "✅ Tuile placée avec succès !\n";
    else
        std::cout << "❌ Placement invalide !\n";

    joueurActuel = (joueurActuel + 1) % joueurs.size();
}

void Jeu::bouclePrincipale() {
    for (int i = 0; i < 10; ++i)
        tourDeJeu();

    std::cout << "\nFin du jeu !" << std::endl;
}