#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "Common.hpp"
#include "Tuile.hpp"

class Joueur;

class Plateau {
private:
    int nbJoueurs;
    int tailleGrille;
    std::vector<std::vector<char>> grille;
    std::vector<std::vector<char>> bonus; 
    std::string couleurCase(char c) const;
    bool estCaseBonusValide(int r, int c) const;

public:
    Plateau(int nombreJoueurs, const std::vector<std::string>& nomsJoueurs);
    void initialiserBonusesFixes();
    void afficherGrille() const;
    int getTailleGrille() const;
    int getNbJoueurs() const;
    bool estPositionValide(const Coordonnee& pos) const;
    bool empieteSurAutre(int idJoueur, const Tuile& tuile, const Coordonnee& pos) const;
    bool toucheTerritoireParCote(int idJoueur, const Tuile& tuile, const Coordonnee& pos) const;
    bool placerTuile(const Tuile& tuile, const Coordonnee& pos, int idJoueur);
    void appliquerBonusesAprèsPlacement(int idJoueur, std::vector<Joueur>& joueurs);
    int plusGrandCarrePour(int idJoueur) const;
    int nombreCasesPour(int idJoueur) const;
    Coordonnee convertirCase(const std::string& input) const;
    void activerBonus(int r, int c, int idJoueur, std::vector<Joueur>& joueurs);
    bool retirerPierre(int r, int c); 
    void utiliserCoupon(int idJoueur, std::deque<Tuile>& pioche, std::vector<Joueur>& joueurs);
    Tuile choisirTuileAvecCoupon(int idJoueur, std::deque<Tuile>& pioche);

};
#endif