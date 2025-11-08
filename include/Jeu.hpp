#ifndef JEU_HPP
#define JEU_HPP

#include <vector>
#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Tuile.hpp"
#include "tuilesDef.hpp" // 🔥 Ajouté

class Jeu {
private:
    Plateau plateau;
    std::vector<Joueur> joueurs;
    std::vector<Tuile> tuilesDisponibles;
    int joueurActuel;

public:
    Jeu(const std::vector<std::string>& noms);

    void tourDeJeu();
    void bouclePrincipale();
};

#endif

