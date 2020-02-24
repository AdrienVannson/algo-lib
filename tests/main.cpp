/*
 * L'objectif de ce fichier n'est pas de complètement tester la validité
 * des implémentations mais de vérifier que tout compile correctemment
 */

#include "algolib.hpp"


// Maths
void testerExponentiationRapide ()
{
    assert(getPuissance(2, 7) == 128);
}

void testerFraction ()
{
    const Fraction<int> a(3, 4), b(1, 3);
    const Fraction<int> r = a - b;

    assert(r.num() == 5 && r.den() == 12);
}

void testerPGCD_PPCM ()
{
    assert(PGCD(42, 13*14) == 14);
    assert(PPCM(2*7, 2*13) == 2*7*13);
}


int main ()
{
    // Maths
    testerExponentiationRapide();
    testerFraction();
    testerPGCD_PPCM();
}
