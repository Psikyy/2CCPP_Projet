#ifndef TUILE_HPP
#define TUILE_HPP

#include <vector>
#include <string>
#include "Common.hpp"

class Tuile {
public:
    Tuile() = default;
    Tuile(const std::vector<Coordonnee>& formeInitiale);
    void rotate();
    void flip();
    const std::vector<Coordonnee>& getForme() const;
    void afficherApercu() const;

private:
    std::vector<Coordonnee> forme;
    void normaliser();
};

#endif