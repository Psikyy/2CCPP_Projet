#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <vector>
#include "Common.hpp"

class Joueur {
public:
    Joueur(std::string nom, std::string couleur, int id);

    std::string getNom() const;
    std::string getCouleur() const;
    int getId() const;
    int getCoupons() const;
    Coordonnee getTuileDepart() const;

    void ajouterCoupon();
    bool utiliserCoupon();
    void setTuileDepart(Coordonnee c);

private:
    std::string nom;
    std::string couleur;
    int id;
    int couponsEchange;
    Coordonnee tuileDepart;
};

#endif