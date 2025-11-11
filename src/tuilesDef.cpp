#include "../include/tuilesDef.hpp"
#include <iostream>
#include "../include/Tuile.hpp"

std::vector<Tuile> chargerTuiles() {
    std::vector<Tuile> tuiles;
    tuiles.push_back(Tuile({{0,0}, {1,0}, {2,0}})); 
    tuiles.push_back(Tuile({{0,0}, {0,1}, {1,0}, {1,1}}));
    tuiles.push_back(Tuile({{0,0}, {0,1}, {0,2}}));
    tuiles.push_back(Tuile({{0,0}, {1,0}, {2,0}, {1,1}}));
    tuiles.push_back(Tuile({{0,1}, {0,2}, {1,0}, {1,1}}));
    tuiles.push_back(Tuile({{0,1}, {1,1}, {2,1}, {2,0}}));
    tuiles.push_back(Tuile({{0,0}, {1,0}, {1,1}, {1,2}}));
    tuiles.push_back(Tuile({{1,0}, {0,1}, {1,1}, {1,2}, {2,1}}));
    tuiles.push_back(Tuile({{0,0}, {0,1}, {0,2}, {1,1}}));
    tuiles.push_back(Tuile({{0,0}, {0,1}, {0,2}, {0,3}}));

    return tuiles;
}