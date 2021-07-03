#include "../Headers/Matrice.hpp"

#include <stdexcept>
#include <iostream>
#include <cassert>

Matrice::Matrice(std::size_t x, std::size_t y, int n) noexcept : m_content(x, std::vector(y, n)) {}

std::size_t Matrice::NumberLines() const noexcept { return m_content.size(); }
std::size_t Matrice::NumberColumns() const noexcept { return m_content[0].size(); }

std::vector<int> Matrice::GetLine(std::size_t index) const noexcept {
    
    if (index < NumberLines()) {
        
        return m_content[index];

    } else throw std::runtime_error{""};
    
}

std::vector<int> Matrice::GetColumn(std::size_t index) const noexcept {

    if (index < NumberColumns()) {

        std::vector<int> column;
        for (const std::vector<int> &v : m_content) column.push_back(v[index]);

        return column;
        
    } else throw std::runtime_error{""};

}

void Matrice::AddLine(const std::vector<int> &line) {

    if (line.size() == NumberColumns()) {

        m_content.push_back(line);

    } else throw std::runtime_error{""};

}

void Matrice::AddColumn(const std::vector<int> &column) {

    if (column.size() == NumberLines()) {

        for (std::size_t i{0}; i < NumberLines(); i++) m_content[i].push_back(column[i]);

    } else throw std::runtime_error{""};

}

void Matrice::RemoveLine() {

    if (NumberLines() > 0) {

        m_content.pop_back();

    } else throw std::runtime_error{""};

}

void Matrice::RemoveColumn() {

    if (NumberColumns() > 0) {

        for (std::vector<int> &v : m_content) v.pop_back();

    } else throw std::runtime_error{""};

}

Matrice Matrice::Transpose() const noexcept {

    Matrice t{NumberColumns(), NumberLines()};
    for (std::size_t x{0}; x < NumberLines(); x++) {
        
        for(std::size_t y{0}; y < NumberColumns(); y++) t(y, x) = (*this)(x, y);

    }

    return t;

}

Matrice operator+(const Matrice &l, const Matrice &r) {

    if (l.NumberLines() == r.NumberLines() && l.NumberColumns() == r.NumberColumns()) {

        Matrice t{l};
        for (std::size_t x{0}; x < t.NumberLines(); x++) {

            for (std::size_t y{0}; y < t.NumberColumns(); y++) t(x, y) += r(x, y);

        }

        return t;

    } else throw std::runtime_error{"Error : Matrices dimensions does not equals"};

}

Matrice operator*(const Matrice &l, const Matrice &r) {

    if (l.NumberColumns() == r.NumberLines()) {

        Matrice result{l.NumberLines(), r.NumberColumns()};

        for (std::size_t x{0}; x < l.NumberLines(); x++) {

            for (std::size_t y{0}; y < r.NumberColumns(); y++) {

                result(x, y) = ScalarCalcul(l.m_content[x], r.Transpose().m_content[y]);

            }

        }

        return result;

    } else throw std::runtime_error{"Error : Matrices dimensions does not equals"};

}

Matrice operator*(const Matrice &m, int n) noexcept {

    Matrice t{m};
    for (std::size_t x{0}; x < t.NumberLines(); x++) {

        for (std::size_t y{0}; y < t.NumberColumns(); y++) t(x, y) *= n;

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

    for (std::size_t x{0}; x < m.NumberLines(); x++) {

        for (std::size_t y{0}; y < m.NumberColumns(); y++) flux << m(x, y) << ' ';
        if (x < m.NumberLines()-1) flux << std::endl;

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