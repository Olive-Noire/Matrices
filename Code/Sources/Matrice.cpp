#include "../Headers/Matrice.hpp"

Matrice::Matrice(std::size_t x, std::size_t y) noexcept {



}

std::size_t Matrice::Lines() const noexcept {}
std::size_t Matrice::Columns() const noexcept {}

Matrice Matrice::Transpose() const noexcept {



}

Matrice operator+(const Matrice &l, const Matrice &r) noexcept {



}

Matrice operator*(const Matrice &l, const Matrice &r) noexcept {



}

Matrice operator*(const Matrice &m, int n) noexcept {



}

Matrice& Matrice::operator+=(const Matrice &m) noexcept {

    *this = *this+m;
    return *this;

}

Matrice& Matrice::operator*=(const Matrice &m) noexcept {

    *this = *this*m;
    return *this;

}

Matrice& Matrice::operator*=(int n) noexcept {

    *this = *this*n;
    return *this;

}

std::ostream& operator<<(std::ostream &flux, const Matrice &m) {

    flux << "";
    return flux;

}

int& Matrice::operator()(std::size_t x, std::size_t y) const {}
int& Matrice::operator()(std::size_t x, std::size_t y) {}