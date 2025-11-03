#ifndef COMMON_HPP
#define COMMON_HPP

struct Coordonnee {
    int ligne;
    int col;

    bool operator==(const Coordonnee& other) const {
        return ligne == other.ligne && col == other.col;
    }
};

struct Case {
    int idJoueur = 0;
};

#endif