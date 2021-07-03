#include "../Headers/Matrix.hpp"
#include "../Headers/Tests.hpp"

#include <iostream>

int main() {

    #ifdef DEBUG

    test_addition();
    test_multiplication_entier();
    test_multiplication_matrice();
    test_transposition();
    test_affichage();

    std::cout << "Tests effectues !\n";

    #endif // DEBUG

    std::cin.get();

    return 0;

}