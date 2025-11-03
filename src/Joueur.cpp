#include "../include/Joueur.hpp"

Joueur::Joueur(std::string nom, std::string couleur, int id)
    : nom(nom),
      couleur(couleur),
      id(id),
      couponsEchange(1),
      tuileDepart({-1, -1}) 
{
}

std::string Joueur::getNom() const { return nom; }
std::string Joueur::getCouleur() const { return couleur; }
int Joueur::getId() const { return id; }
int Joueur::getCoupons() const { return couponsEchange; }
Coordonnee Joueur::getTuileDepart() const { return tuileDepart; }

void Joueur::ajouterCoupon() {
    couponsEchange++;
}

bool Joueur::utiliserCoupon() {
    if (couponsEchange > 0) {
        couponsEchange--;
        return true;
    }
    return false;
}

void Joueur::setTuileDepart(Coordonnee c) {
    tuileDepart = c;
}