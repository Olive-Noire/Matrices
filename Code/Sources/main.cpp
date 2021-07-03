#include <iostream>
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

    assert(addition.Lines() == resultat.Lines() && "L'addition n'est pas correcte.");
    assert(addition.Columns() == resultat.Columns() && "L'addition n'est pas correcte.");
    for (std::size_t i{0}; i < addition.Lines(); i++) {

        for (std::size_t j{0}; j < addition.Columns(); j++) {

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

    assert(resultat.Lines() == multiplication.Lines() && "La multiplication par un entier n'est pas correcte.");
    assert(resultat.Columns() == multiplication.Columns() && "La multiplication par un entier n'est pas correcte.");
    for (std::size_t i{0}; i < multiplication.Lines(); i++) {

        for (std::size_t j{0}; j < multiplication.Columns(); j++) {

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

    assert(resultat.Lines() == multiplication.Lines() && "La multiplication par une matrice n'est pas correcte.");
    assert(resultat.Columns() == multiplication.Columns() && "La multiplication par une matrice n'est pas correcte.");
    for (std::size_t i{0}; i < multiplication.Lines(); i++) {

        for (std::size_t j{0}; j < multiplication.Columns(); j++) {

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

    assert(resultat.Lines() == transposee.Lines() && "La transposition n'est pas correcte.");
    assert(resultat.Columns() == transposee.Columns() && "La transposition n'est pas correcte.");
    for (std::size_t i{0}; i < transposee.Lines(); i++) {

        for (std::size_t j{0}; j < transposee.Columns(); j++) {

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

int main() {

    test_addition();
    test_multiplication_entier();
    //test_multiplication_matrice();
    //test_transposition();
    test_affichage();

    std::cin.get();

    return 0;

}