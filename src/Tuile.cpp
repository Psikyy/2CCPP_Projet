#include "../include/Tuile.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

Tuile::Tuile(const std::vector<Coordonnee>& formeInitiale) : forme(formeInitiale) {
    normaliser();
}

void Tuile::rotate() {
    for (Coordonnee& c : forme) {
        int tempLigne = c.ligne;
        c.ligne = c.col;
        c.col = -tempLigne;
    }
    normaliser();
}

void Tuile::flip() {
    for (Coordonnee& c : forme) {
        c.col = -c.col;
    }
    normaliser();
}

void Tuile::normaliser() {
    if (forme.empty()) return;

    int minLigne = forme[0].ligne;
    int minCol = forme[0].col;

    for (const Coordonnee& c : forme) {
        if (c.ligne < minLigne) minLigne = c.ligne;
        if (c.col < minCol) minCol = c.col;
    }

    for (Coordonnee& c : forme) {
        c.ligne -= minLigne;
        c.col -= minCol;
    }
}

const std::vector<Coordonnee>& Tuile::getForme() const {
    return forme;
}

void Tuile::afficherApercu() const {
    if (forme.empty()) {
        std::cout << "  (Tuile vide)" << std::endl;
        return;
    }

    int maxLigne = 0;
    int maxCol = 0;
    for (const Coordonnee& c : forme) {
        if (c.ligne > maxLigne) maxLigne = c.ligne;
        if (c.col > maxCol) maxCol = c.col;
    }

    std::vector<std::string> apercu(maxLigne + 1, std::string(maxCol + 1, ' '));
    for (const Coordonnee& c : forme) {
        apercu[c.ligne][c.col] = '#';
    }

    for (const std::string& ligne : apercu) {
        std::cout << "  " << ligne << std::endl;
    }
}