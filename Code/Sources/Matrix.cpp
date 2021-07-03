#include "../Headers/Matrix.hpp"

#include <stdexcept>
#include <iostream>
#include <cassert>
#include <numeric>

Matrix::Matrix(std::size_t x, std::size_t y, int n) noexcept : m_content(x, std::vector(y, n)) {}

std::size_t Matrix::NumberLines() const noexcept { return m_content.size(); }
std::size_t Matrix::NumberColumns() const noexcept { return m_content[0].size(); }

std::vector<int> Matrix::GetLine(std::size_t index) const noexcept {
    
    if (index >= NumberLines()) throw std::runtime_error{"Error : index of line too much big"};
    return m_content[index];
    
}

std::vector<int> Matrix::GetColumn(std::size_t index) const noexcept {

    if (index >= NumberColumns()) throw std::runtime_error{"Error : index of column too much big"};

    std::vector<int> column;
    for (const std::vector<int> &v : m_content) column.push_back(v[index]);

    return column;

}

void Matrix::AddLine(const std::vector<int> &line) {

    if (line.size() != NumberColumns()) throw std::runtime_error{"Error : Size of added line does not equals number of columns"};
    m_content.push_back(line);

}

void Matrix::AddColumn(const std::vector<int> &column) {

    if (column.size() != NumberLines()) throw std::runtime_error{"Error : Size of added column does not equals number of lines"};
    for (std::size_t i{0}; i < NumberLines(); i++) m_content[i].push_back(column[i]);

}

void Matrix::RemoveLine() {

    if (NumberLines() == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};
    m_content.pop_back();

}

void Matrix::RemoveColumn() {

    if (NumberColumns() == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};
    for (std::vector<int> &v : m_content) v.pop_back();

}

Matrix Matrix::Transpose() const noexcept {

    Matrix t{NumberColumns(), NumberLines()};
    for (std::size_t x{0}; x < NumberLines(); x++) {
        
        for(std::size_t y{0}; y < NumberColumns(); y++) t(y, x) = (*this)(x, y);

    }

    return t;

}

Matrix operator+(const Matrix &l, const Matrix &r) {

    if (l.NumberLines() != r.NumberLines() || l.NumberColumns() != r.NumberColumns()) throw std::runtime_error{"Error : Matrixs dimensions does not equals"};

    Matrix t{l};
    for (std::size_t x{0}; x < t.NumberLines(); x++) {

        for (std::size_t y{0}; y < t.NumberColumns(); y++) t(x, y) += r(x, y);

    }

    return t;

}

Matrix operator*(const Matrix &l, const Matrix &r) {

    if (l.NumberColumns() != r.NumberLines()) throw std::runtime_error{"Error : Matrixs dimensions does not equals"};

    Matrix result{l.NumberLines(), r.NumberColumns()};
    for (std::size_t x{0}; x < l.NumberLines(); x++) {

        for (std::size_t y{0}; y < r.NumberColumns(); y++) {

            result(x, y) = std::inner_product(l.GetLine(x).cbegin(), l.GetLine(x).cend(), r.Transpose().GetColumn(y).cbegin(), 0);

        }

    }

    return result;

}

Matrix operator*(const Matrix &m, int n) noexcept {

    Matrix t{m};
    for (std::size_t x{0}; x < t.NumberLines(); x++) {

        for (std::size_t y{0}; y < t.NumberColumns(); y++) t(x, y) *= n;

    }

    return t;

}

Matrix& Matrix::operator+=(const Matrix &m) {

    *this = *this+m;
    return *this;

}

Matrix& Matrix::operator*=(const Matrix &m) {

    *this = *this*m;
    return *this;

}

Matrix& Matrix::operator*=(int n) noexcept {

    *this = *this*n;
    return *this;

}

std::ostream& operator<<(std::ostream &flux, const Matrix &m) {

    for (std::size_t x{0}; x < m.NumberLines(); x++) {

        for (std::size_t y{0}; y < m.NumberColumns(); y++) flux << m(x, y) << ' ';
        if (x < m.NumberLines()-1) flux << std::endl;

    }

    return flux;

}

const int& Matrix::operator()(std::size_t x, std::size_t y) const {
    
    if (x > NumberLines() || y > NumberColumns()) throw std::runtime_error{"Error : index is too much big"};
    return m_content[x][y];

}

int& Matrix::operator()(std::size_t x, std::size_t y) {
    
    if (x > NumberLines() || y > NumberColumns()) throw std::runtime_error{"Error : index is too much big"};
    return m_content[x][y];
    
}