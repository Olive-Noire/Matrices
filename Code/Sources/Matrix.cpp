#include "../Headers/Matrix.hpp"

#include <stdexcept>
#include <iostream>
#include <numeric>

Matrix::Matrix(std::size_t x, std::size_t y, int n) noexcept : m_lines{x}, m_columns{y}, m_content(x*y, n) {}

std::size_t Matrix::NumberLines() const noexcept { return m_lines; }
std::size_t Matrix::NumberColumns() const noexcept { return m_columns; }

std::vector<int> Matrix::GetLine(std::size_t index) const {
    
    if (index >= m_lines) throw std::runtime_error{"Error : index of line too much big"};

    std::vector<int> result;

    for (std::size_t i{0}; i < m_columns; i++) result.push_back(m_content[index*m_columns+i]);
    return result;
    
}

std::vector<int> Matrix::GetColumn(std::size_t index) const {

    if (index >= NumberColumns()) throw std::runtime_error{"Error : index of column too much big"};

    std::vector<int> column;
    for (std::size_t i{0}; i < m_lines; i++) column.push_back((*this)(i, index));

    return column;

}

void Matrix::AddLine(const std::vector<int> &line) {

    if (line.size() != NumberColumns()) throw std::runtime_error{"Error : Size of added line does not equals number of columns"};

    for (int i : line) m_content.push_back(i);
    m_lines++;

}

void Matrix::AddColumn(const std::vector<int> &column) {

    if (column.size() != NumberLines()) throw std::runtime_error{"Error : Size of added column does not equals number of lines"};

    for (std::size_t i{0}; i < NumberLines(); i++) m_content.insert(m_content.cbegin()+i*m_lines+m_columns, column[i]);
    m_columns++;

}

void Matrix::RemoveLine() {

    if (NumberLines() == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};

    for (std::size_t i{0}; i < m_columns; i++) m_content.pop_back();
    m_lines--;

}

void Matrix::RemoveColumn() {

    if (NumberColumns() == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};

    for (std::size_t i{0}; i < m_lines; i++) m_content.erase(m_content.cbegin()+i*m_columns-1);
    m_columns--;

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

Matrix operator-(const Matrix &l, const Matrix &r) {

    if (l.NumberLines() != r.NumberLines() || l.NumberColumns() != r.NumberColumns()) throw std::runtime_error{"Error : Matrixs dimensions does not equals"};

    Matrix t{l};
    for (std::size_t x{0}; x < t.NumberLines(); x++) {

        for (std::size_t y{0}; y < t.NumberColumns(); y++) t(x, y) -= r(x, y);

    }

    return t;

}

Matrix operator*(const Matrix &l, const Matrix &r) {

    if (l.NumberColumns() != r.NumberLines()) throw std::runtime_error{"Error : Matrixs dimensions does not equals"};

    Matrix result{l.NumberLines(), r.NumberColumns()};
    for (std::size_t x{0}; x < l.NumberLines(); x++) {

        for (std::size_t y{0}; y < r.NumberColumns(); y++) {

            std::vector<int> line{l.GetLine(x)};
            result(x, y) = std::inner_product(line.cbegin(), line.cend(), r.GetColumn(y).cbegin(), 0);

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

Matrix& Matrix::operator-=(const Matrix &m) {

    *this = *this-m;
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

bool operator==(const Matrix &l, const Matrix &r) noexcept { return l.m_content == r.m_content; }
bool operator!=(const Matrix &l, const Matrix &r) noexcept { return !(l==r); }

std::ostream& operator<<(std::ostream &flux, const Matrix &m) {

    for (std::size_t x{0}; x < m.NumberLines(); x++) {

        for (std::size_t y{0}; y < m.NumberColumns(); y++) flux << m(x, y) << ' ';
        if (x < m.NumberLines()-1) flux << std::endl;

    }

    return flux;

}

const int& Matrix::operator()(std::size_t x, std::size_t y) const {
    
    if (x > NumberLines() || y > NumberColumns()) throw std::runtime_error{"Error : index is too much big"};
    return m_content[x*m_columns+y];

}

int& Matrix::operator()(std::size_t x, std::size_t y) {
    
    if (x > NumberLines() || y > NumberColumns()) throw std::runtime_error{"Error : index is too much big"};
    return m_content[x*m_columns+y];
    
}