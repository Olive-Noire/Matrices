#ifdef _DEBUG

#include "../Headers/Tests.hpp"

#include <cassert>

#include "../Headers/Matrice.hpp"

void test_addition() {

    Matrice m1{2, 3};
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice m2{2, 3};
    m2(0, 0) = 0;
    m2(0, 1) = 4;
    m2(0, 2) = 9;
    m2(1, 0) = 4;
    m2(1, 1) = -7;
    m2(1, 2) = 1;

    Matrice resultat{2, 3};
    resultat(0, 0) = 1;
    resultat(0, 1) = 6;
    resultat(0, 2) = 12;
    resultat(1, 0) = 7;
    resultat(1, 1) = -3;
    resultat(1, 2) = 7;

    const Matrice addition{m1+m2};

    assert(addition.NumberLines() == resultat.NumberLines() && "L'addition n'est pas correcte.");
    assert(addition.NumberColumns() == resultat.NumberColumns() && "L'addition n'est pas correcte.");
    for (std::size_t i{0}; i < addition.NumberLines(); i++) {

        for (std::size_t j{0}; j < addition.NumberColumns(); j++) {

            assert(resultat(i, j) == addition(i, j) && "L'addition n'est pas correcte.");

        }

    }

}

void test_multiplication_entier() {

    Matrice m1{2, 3};
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice resultat{2, 3};
    resultat(0, 0) = 2;
    resultat(0, 1) = 4;
    resultat(0, 2) = 6;
    resultat(1, 0) = 6;
    resultat(1, 1) = 8;
    resultat(1, 2) = 12;

    const Matrice multiplication{m1*2};

    assert(resultat.NumberLines() == multiplication.NumberLines() && "La multiplication par un entier n'est pas correcte.");
    assert(resultat.NumberColumns() == multiplication.NumberColumns() && "La multiplication par un entier n'est pas correcte.");
    for (std::size_t i{0}; i < multiplication.NumberLines(); i++) {

        for (std::size_t j{0}; j < multiplication.NumberColumns(); j++) {

            assert(resultat(i, j) == multiplication(i, j) && "La multiplication par un entier n'est pas correcte.");

        }
        
    }

}

void test_multiplication_matrice() {

    Matrice m1{2, 3};
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice m2{3, 2};
    m2(0, 0) = 0;
    m2(0, 1) = 4;
    m2(1, 0) = 4;
    m2(1, 1) = -7;
    m2(2, 0) = 9;
    m2(2, 1) = 1;

    Matrice resultat{2, 2};
    resultat(0, 0) = 35;
    resultat(0, 1) = -7;
    resultat(1, 0) = 70;
    resultat(1, 1) = -10;

    const Matrice multiplication{m1*m2};

    assert(resultat.NumberLines() == multiplication.NumberLines() && "La multiplication par une matrice n'est pas correcte.");
    assert(resultat.NumberColumns() == multiplication.NumberColumns() && "La multiplication par une matrice n'est pas correcte.");
    for (std::size_t i{0}; i < multiplication.NumberLines(); i++) {

        for (std::size_t j{0}; j < multiplication.NumberColumns(); j++) {

            assert(resultat(i, j) == multiplication(i, j) && "La multiplication par une matrice n'est pas correcte.");

        }

    }

}

void test_transposition() {

    Matrice m1{2, 3};
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice resultat{3, 2};
    resultat(0, 0) = 1;
    resultat(0, 1) = 3;
    resultat(1, 0) = 2;
    resultat(1, 1) = 4;
    resultat(2, 0) = 3;
    resultat(2, 1) = 6;

    const Matrice transposee{m1.Transpose()};

    assert(resultat.NumberLines() == transposee.NumberLines() && "La transposition n'est pas correcte.");
    assert(resultat.NumberColumns() == transposee.NumberColumns() && "La transposition n'est pas correcte.");
    for (std::size_t i{0}; i < transposee.NumberLines(); i++) {

        for (std::size_t j{0}; j < transposee.NumberColumns(); j++) {

            assert(resultat(i, j) == transposee(i, j) && "La transposition n'est pas correcte.");

        }

    }

}

void test_affichage() {

    Matrice m1{2, 2};
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 3;

    Matrice m2{2, 2};
    m2(0, 0) = 0;
    m2(0, 1) = 4;
    m2(1, 0) = 4;
    m2(1, 1) = -7;

    std::cout << m1 << "\n";
    std::cout << m1+m2 << "\n";
    std::cout << m1+m2+m2 << "\n";

}

#endif // _DEBUG