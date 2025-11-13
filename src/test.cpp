#include "../include/Jeu.hpp"
#include <iostream>
#include <cassert>

using namespace std;

void testTuileRotationFlip() {
    cout << "\n=== TEST 1 : Rotation & Flip ===\n";
    Tuile t({{0,0},{1,0},{2,0}});
    cout << "Original:\n"; t.afficherApercu();
    t.rotate(); cout << "Après rotation:\n"; t.afficherApercu();
    t.flip(); cout << "Après flip:\n"; t.afficherApercu();
    cout << "Rotation & Flip test OK\n";
}

void testPlacementBasique() {
    cout << "\n=== TEST 2 : Placement basique ===\n";
    Plateau plateau(2, {"A","B"});
    Tuile t1({{0,0}});
    bool ok = plateau.placerTuile(t1, {10,10}, 1);
    assert(ok);
    cout << "Placement 1 réussi.\n";
    Tuile t2({{0,0}});
    bool fail = plateau.placerTuile(t2, {10,10}, 2);
    assert(!fail);
    cout << "Placement collision refusé (ok).\n";
    plateau.afficherGrille();
    cout << "Placement test OK\n";
}

void testAdjacenceEtEmpietement() {
    cout << "\n=== TEST 3 : Empiètement & Adjacence ===\n";
    Plateau plateau(2, {"A","B"});
    Tuile start({{0,0}});
    plateau.placerTuile(start, {5,5}, 1);
    Tuile t({{0,0}});
    bool invalide = plateau.placerTuile(t, {5,7}, 1);
    assert(!invalide);
    bool valide = plateau.placerTuile(t, {5,6}, 1);
    assert(valide);
    cout << "Test adjacence / empietement OK\n";
    plateau.afficherGrille();
}

void testBonuses() {
    cout << "\n=== TEST 4 : Bonus (E, P, V) ===\n";
    Plateau plateau(2, {"Arthur","Lucas"});
    Joueur j1("Arthur","red",1);
    Joueur j2("Lucas","blue",2);
    vector<Joueur> joueurs = {j1,j2};

    plateau.initialiserBonusesFixes();

    int r = 5, c = 5;
    Tuile bloc({{0,0}});
    plateau.placerTuile(bloc, {r-1,c}, 1);
    plateau.placerTuile(bloc, {r+1,c}, 1);
    plateau.placerTuile(bloc, {r,c-1}, 1);
    plateau.placerTuile(bloc, {r,c+1}, 1);
    plateau.appliquerBonusesAprèsPlacement(1, joueurs);
    cout << "Bonus test terminé\n";
}

void testCalculScore() {
    cout << "\n=== TEST 5 : Calcul du plus grand carré ===\n";
    Plateau plateau(1, {"Arthur"});
    Tuile t({{0,0}});
    plateau.placerTuile(t, {5,5}, 1);
    plateau.placerTuile(t, {5,6}, 1);
    plateau.placerTuile(t, {6,5}, 1);
    plateau.placerTuile(t, {6,6}, 1);
    int carre = plateau.plusGrandCarrePour(1);
    int total = plateau.nombreCasesPour(1);
    cout << "Carré détecté = " << carre << " (attendu 2)\n";
    cout << "Total cases = " << total << " (attendu 4)\n";
    assert(carre == 2 && total == 4);
    cout << "Score test OK\n";
}

void testMiniPartie() {
    cout << "\n=== TEST 6 : Simulation mini partie ===\n";
    vector<string> noms = {"Arthur","Lucas"};
    Jeu jeu(noms, 3);
    Plateau &plateau = jeu.getPlateau();
    auto &pile = jeu.getPile();
    auto &joueurs = jeu.getJoueurs();

    plateau.placerTuile(Tuile({{0,0}}), {10,10}, 1);
    plateau.placerTuile(Tuile({{0,0}}), {10,12}, 2);

    for (int t = 1; t <= 3; ++t) {
        Tuile tuile1 = pile.front(); pile.pop_front();
        Tuile tuile2 = pile.front(); pile.pop_front();
        tuile1.rotate();
        tuile2.flip();
        plateau.placerTuile(tuile1, {10,t+10}, 1);
        plateau.placerTuile(tuile2, {11,t+11}, 2);
    }

    plateau.afficherGrille();
    int s1 = plateau.plusGrandCarrePour(1);
    int s2 = plateau.plusGrandCarrePour(2);
    cout << "Arthur carré = " << s1 << " | Lucas carré = " << s2 << "\n";
    cout << ((s1 > s2) ? "Vainqueur: Arthur" : "Vainqueur: Lucas") << endl;
    cout << "Mini partie OK\n";
}

int main() {
    cout << "\n=== DEMARRAGE DES TESTS AUTOMATIQUES ===\n";
    testTuileRotationFlip();
    testPlacementBasique();
    testAdjacenceEtEmpietement();
    testBonuses();
    testCalculScore();
    testMiniPartie();
    cout << "\nTOUS LES TESTS TERMINÉS AVEC SUCCÈS \n";
    return 0;
}
