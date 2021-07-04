#include "../Headers/Matrix.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <numeric>

#include "../Headers/MatrixTypes.hpp"

Matrix::Matrix(std::size_t x, std::size_t y, int n) noexcept : m_lines{x}, m_columns{y}, m_content(x*y, n) {}

Matrix::Matrix(std::size_t x, std::size_t y, const std::vector<int> &c) : m_lines{x}, m_columns{y}, m_content{c} {

    if (c.size() != x*y) throw std::runtime_error{"Error : Vector size is different of dimensions"};

}

Matrix::Matrix(std::size_t x, std::size_t y, const std::vector<std::vector<int>> &c) : m_lines{x}, m_columns{y} {

    if (c.size() != x) throw std::runtime_error{"Error : Vector size is different of dimensions (horizontal)"};

    for (std::size_t i{0}; i < x; i++) {

        if (c[i].size() != y) throw std::runtime_error{"Error : Vector size is different of dimensions (vertical)"};
        for (std::size_t j{0}; j < y; j++) m_content.push_back(c[i][j]);

    }

}

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

void Matrix::AddLines(std::vector<int> line, std::size_t l) {

    if (line == std::vector<int>{}) line = std::vector<int>(m_columns, 0);
    if (line.size() != m_columns && !Empty()) throw std::runtime_error{"Error : Size of added line does not equals number of columns"};

    for (std::size_t i{0}; i < l; i++) for (int add : line) m_content.push_back(add);
    m_lines += l;

}

void Matrix::AddLines(std::size_t n) { AddLines({}, n); }

void Matrix::AddColumns(std::vector<int> column, std::size_t c) {

    if (column == std::vector<int>{}) column = std::vector<int>(m_lines, 0);
    if (column.size() != m_lines && !Empty()) throw std::runtime_error{"Error : Size of added column does not equals number of lines"};

    for (std::size_t i{0}; i < c; i++) for (std::size_t add{0}; add < m_lines; add++) m_content.insert(m_content.cbegin()+add*m_lines+m_columns, column[add]);
    m_columns += c;

}

void Matrix::AddColumns(std::size_t c) { AddColumns({}, c); }

void Matrix::RemoveLines(std::size_t l) {

    if (m_lines == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};
    if (l >= m_lines) throw std::runtime_error{"Error : Can't remove over size"};

    for (std::size_t i{0}; i < l; i++) for (std::size_t remove{0}; remove < m_columns; remove++) m_content.pop_back();
    m_lines -= l;

}

void Matrix::RemoveColumns(std::size_t c) {

    if (m_columns == 0) throw std::runtime_error{"Error : Can't remove, beacause matrix is empty"};
    if (c >= m_columns) throw std::runtime_error{"Error : Can't remove over size"};

    for (std::size_t i{0}; i < c; i++) for (std::size_t remove{0}; remove < m_lines; remove++) m_content.erase(m_content.cbegin()+remove*m_columns-1);
    m_columns -= c;

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

Matrix Matrix::operator!() const {

    if (!Matrix_Type::Square::Is(*this)) throw std::runtime_error{"Error : Can't calcul inverse of matrix not square"};

    Matrix inverse{*this};
    if (m_lines == 2) {

        inverse(0, 0) = (*this)(1, 1);
        inverse(0, 1) = -(*this)(0, 1);
        inverse(1, 0) = -(*this)(1, 0);
        inverse(1, 1) = (*this)(0, 0);

        inverse *= 1/((*this)(0, 0)*(*this)(1, 1)-(*this)(0, 1)*(*this)(1, 0));

    } else throw std::domain_error{"Error : Inverse of square matrix different of 2 is not implemented"};
    
    if (*this*inverse != Matrix_Type::Unit::Make(m_lines)) throw std::runtime_error{"Error : Inverse of this matrix does not exist (with integer)"};
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

Matrix pow(Matrix m, std::size_t p) {

    if (!Matrix_Type::Square::Is(m)) throw std::runtime_error{"Error : Can't calcul power of matrix not square"};

    if (p == 0) return Matrix_Type::Unit::Make(m.m_lines);
    if (p == 1) return m;

    Matrix t{m};
    for (std::size_t i{1}; i < p; i++) m *= t;

    return m;

}