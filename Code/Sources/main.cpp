#include "../Headers/Matrice.hpp"
#include "../Headers/Tests.hpp"

#include <iostream>

int main() {

    #ifdef _DEBUG

    test_addition();
    test_multiplication_entier();
    test_multiplication_matrice();
    test_transposition();
    test_affichage();

    #endif // _DEBUG

    std::cin.get();

    return 0;

}