#include "../Headers/Matrice.hpp"

#include <stdexcept>

Matrice::Matrice(std::size_t x, std::size_t y) noexcept : m_content(x, std::vector(y, 0)) {}

std::size_t Matrice::Lines() const noexcept { return m_content.size(); }
std::size_t Matrice::Columns() const noexcept { return m_content[0].size(); }

Matrice Matrice::Transpose() const noexcept {

    Matrice t{Columns(), Lines()};
    for (std::size_t x{0}; x < Lines(); x++) {
        
        for(std::size_t y{0}; y < Columns(); y++) t(y, x) = this->operator()(x, y);

    }

    return t;

}

Matrice operator+(const Matrice &l, const Matrice &r) {

    if (l.Lines() == r.Lines() && l.Columns() == r.Columns()) {

        Matrice t{l};
        for (std::size_t x{0}; x < t.Lines(); x++) {

            for (std::size_t y{0}; y < t.Columns(); y++) t(x, y) += r(x, y);

        }
        return t;

    } else throw std::runtime_error{"Error : Matrices dimensions does not equals"};

}

Matrice operator*(const Matrice &l, const Matrice &r) {

    if (l.Columns() == r.Lines()) {

        Matrice result{l.Lines(), r.Columns()};

        for (std::size_t x{0}; x < l.Lines(); x++) {

            for (std::size_t y{0}; y < r.Columns(); y++) {

                result(x, y) = ScalarCalcul(l.m_content[x], r.Transpose().m_content[y]);

            }

        }

        return result;

    } else throw std::runtime_error{"Error : Matrices dimensions does not equals"};

}

Matrice operator*(const Matrice &m, int n) noexcept {

    Matrice t{m};
    for (std::size_t x{0}; x < t.Lines(); x++) {

        for (std::size_t y{0}; y < t.Columns(); y++) t(x, y) *= n;

    }

    return t;

}

Matrice& Matrice::operator+=(const Matrice &m) {

    *this = *this+m;
    return *this;

}

Matrice& Matrice::operator*=(const Matrice &m) {

    *this = *this*m;
    return *this;

}

Matrice& Matrice::operator*=(int n) noexcept {

    *this = *this*n;
    return *this;

}

std::ostream& operator<<(std::ostream &flux, const Matrice &m) {

    for (std::size_t x{0}; x < m.Lines(); x++) {

        for (std::size_t y{0}; y < m.Columns(); y++) flux << m(x, y) << ' ';
        flux << std::endl;

    }

    return flux;

}

const int& Matrice::operator()(std::size_t x, std::size_t y) const noexcept { return m_content[x][y]; }
int& Matrice::operator()(std::size_t x, std::size_t y) noexcept { return m_content[x][y]; }

int ScalarCalcul(const std::vector<int> &line, const std::vector<int> &column) {

    if (line.size() == column.size()) {

        int result{0};
        for (std::size_t i{0}; i < line.size(); i++) result += line[i]*column[i];

        return result;

    } else throw std::runtime_error{"Error : Scalar-vectors sizes does not equals"};

}