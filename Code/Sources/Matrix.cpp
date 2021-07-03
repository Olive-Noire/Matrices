#include "../Headers/Matrix.hpp"

#include <algorithm>
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

    if (index >= m_columns) throw std::runtime_error{"Error : index of column too much big"};

    std::vector<int> column;
    for (std::size_t i{0}; i < m_lines; i++) column.push_back((*this)(i, index));

    return column;

}

void Matrix::AddLine(const std::vector<int> &line) {

    if (line.size() != m_columns) throw std::runtime_error{"Error : Size of added line does not equals number of columns"};

    for (int i : line) m_content.push_back(i);
    m_lines++;

}

void Matrix::AddColumn(const std::vector<int> &column) {

    if (column.size() != m_lines) throw std::runtime_error{"Error : Size of added column does not equals number of lines"};

    for (std::size_t i{0}; i < m_lines; i++) m_content.insert(m_content.cbegin()+i*m_lines+m_columns, column[i]);
    m_columns++;

}

void Matrix::RemoveLine(std::size_t s) {

    if (m_lines == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};
    if (s >= m_lines) throw std::runtime_error{"Error : Can't remove over size"};

    for (std::size_t i{0}; i < s; i++) for (std::size_t remove{0}; remove < m_columns; remove++) m_content.pop_back();
    m_lines--;

}

void Matrix::RemoveColumn(std::size_t s) {

    if (m_columns == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};
    if (s >= m_columns) throw std::runtime_error{"Error : Can't remove over size"};

    for (std::size_t i{0}; i < s; i++) for (std::size_t remove{0}; remove < m_lines; remove++) m_content.erase(m_content.cbegin()+remove*m_columns-1);
    m_columns--;

}

Matrix Matrix::Transpose() const noexcept {

    Matrix t{m_columns, m_lines};
    for (std::size_t x{0}; x < m_lines; x++) {
        
        for(std::size_t y{0}; y < m_columns; y++) t(y, x) = (*this)(x, y);

    }

    return t;

}

bool Matrix::Empty() const noexcept { return m_content.empty(); }
void Matrix::Clear() noexcept { m_content.clear(); }
void Matrix::Reverse() { std::reverse(m_content.begin(), m_content.end()); }

Matrix Matrix::MakeNull(std::size_t s) noexcept { return Matrix::MakeSquare(s, 0); }
Matrix Matrix::MakeSquare(std::size_t s, int n) noexcept { return Matrix{s, s, n}; }

Matrix Matrix::MakeUnit(std::size_t s) noexcept {

    Matrix m{Matrix::MakeNull(s)};
    for (std::size_t i{0}; i < s; i++) m(i, i) = 1;

    return m;

}

Matrix Matrix::MakeDiagonal(std::size_t s, int n) noexcept {

    Matrix m{Matrix::MakeSquare(s)};
    for (std::size_t i{0}; i < s; i++) m(i, i) = n;

    return m;

}

Matrix Matrix::MakeUpTriangular(std::size_t s, int n) noexcept {

    Matrix m{Matrix::MakeDiagonal(s, n)};
    for (std::size_t x{0}; x < s; x++) {

        for (std::size_t y{0}; y < s; y++) {

            if (y > x) m(x, y) = n;

        }

    }

    return m;

}

Matrix Matrix::MakeLowTriangular(std::size_t s, int n) noexcept {

    Matrix m{Matrix::MakeDiagonal(s, n)};
    for (std::size_t x{0}; x < s; x++) {

        for (std::size_t y{0}; y < s; y++) {

            if (y < x) m(x, y) = n;

        }

    }

    return m;

}

Matrix Matrix::MakeHollow(std::size_t s, const Matrix &m) noexcept {

    Matrix hollow{Matrix::MakeNull(s)};
    for (std::size_t x{0}; x < s; x++) {

        for (std::size_t y{0}; y < s; y++) {

            if (x != y && x < m.m_lines && y < m.m_columns) hollow(x, y) = m(x, y);

        }

    }

    return hollow;

}

bool Matrix::IsNull() const noexcept { return *this == Matrix::MakeNull(m_lines); }
bool Matrix::IsSquare() const noexcept { return m_lines == m_columns; }
bool Matrix::IsUnit() const noexcept { return *this == Matrix::MakeUnit(m_lines); }
bool Matrix::IsDiagonal() const noexcept { return Empty() && *this == Matrix::MakeDiagonal(m_lines, (*this)(0, 0)); }
bool Matrix::IsUpTriangular() const noexcept { return Empty() && *this == Matrix::MakeUpTriangular(m_lines, (*this)(0, 0)); }
bool Matrix::IsLowTriangular() const noexcept { return Empty() && *this == Matrix::MakeLowTriangular(m_lines, (*this)(0, 0)); }

bool Matrix::IsHollow() const noexcept {

    if (!IsSquare()) return false;
    for (std::size_t i{0}; i < m_lines; i++) if ((*this)(i, i) != 0) return false;

    return true;

}

Matrix Matrix::operator!() const {

    if (!IsSquare()) throw std::runtime_error{"Error : Can't calcul inverse of matrix not square"};

    Matrix inverse{*this};
    if (m_lines == 2) {

        inverse(0, 0) = (*this)(1, 1);
        inverse(0, 1) = -(*this)(0, 1);
        inverse(1, 0) = -(*this)(1, 0);
        inverse(1, 1) = (*this)(0, 0);

        inverse *= 1/((*this)(0, 0)*(*this)(1, 1)-(*this)(0, 1)*(*this)(1, 0));

    } else throw std::domain_error{"Error : Inverse of square matrix different of 2 is not implemented"};
    
    if (*this*inverse != Matrix::MakeUnit(m_lines)) throw std::runtime_error{"Error : Inverse of this matrix does not exist (with integer)"};
    return inverse;

}

Matrix operator+(const Matrix &l, const Matrix &r) {

    if (l.m_lines != r.m_lines || l.m_columns != r.m_columns) throw std::runtime_error{"Error : Matrixs dimensions does not equals"};

    Matrix t{l};
    for (std::size_t x{0}; x < t.m_lines; x++) {

        for (std::size_t y{0}; y < t.m_columns; y++) t(x, y) += r(x, y);

    }

    return t;

}

Matrix operator-(const Matrix &l, const Matrix &r) {

    if (l.m_lines != r.m_lines || l.m_columns != r.m_columns) throw std::runtime_error{"Error : Matrixs dimensions does not equals"};

    Matrix t{l};
    for (std::size_t x{0}; x < t.m_lines; x++) {

        for (std::size_t y{0}; y < t.m_columns; y++) t(x, y) -= r(x, y);

    }

    return t;

}

Matrix operator*(const Matrix &l, const Matrix &r) {

    if (l.m_columns != r.m_lines) throw std::runtime_error{"Error : Matrixs dimensions does not equals"};

    Matrix result{l.m_lines, r.m_columns};
    for (std::size_t x{0}; x < l.m_lines; x++) {

        for (std::size_t y{0}; y < r.m_columns; y++) {

            std::vector<int> line{l.GetLine(x)};
            result(x, y) = std::inner_product(line.cbegin(), line.cend(), r.GetColumn(y).cbegin(), 0);

        }

    }

    return result;

}

Matrix operator*(const Matrix &m, int n) noexcept {

    Matrix t{m};
    for (std::size_t x{0}; x < t.m_lines; x++) {

        for (std::size_t y{0}; y < t.m_columns; y++) t(x, y) *= n;

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
bool operator!=(const Matrix &l, const Matrix &r) noexcept { return !(l == r); }

std::ostream& operator<<(std::ostream &flux, const Matrix &m) {

    for (std::size_t x{0}; x < m.m_lines; x++) {

        for (std::size_t y{0}; y < m.m_columns; y++) flux << m(x, y) << ' ';
        if (x < m.m_lines-1) flux << std::endl;

    }

    return flux;

}

const int& Matrix::operator()(std::size_t x, std::size_t y) const {
    
    if (x > m_lines || y > m_columns) throw std::runtime_error{"Error : index is too much big"};
    return m_content[x*m_columns+y];

}

int& Matrix::operator()(std::size_t x, std::size_t y) {
    
    if (x > m_lines || y > m_columns) throw std::runtime_error{"Error : index is too much big"};
    return m_content[x*m_columns+y];
    
}