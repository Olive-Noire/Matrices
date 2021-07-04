#include "../Headers/MatrixType.hpp"
#include "../Headers/Tests.hpp"

#include <iostream>
#include <ctime>

int main() {

    srand(time(0));

    #ifdef DEBUG

    test_addition();
    test_multiplication_entier();
    test_multiplication_matrice();
    test_transposition();
    test_affichage();

    std::cout << "Tests effectues !\n";

    #endif // DEBUG

    std::cout << Matrix_Type::Random::Make(15, 15, 9, 99);

    std::cin.get();

    return 0;

}