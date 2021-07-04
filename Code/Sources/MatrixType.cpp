#include "../Headers/MatrixType.hpp"

#include <cstdlib>

Matrix Matrix_Type::Empty::Make() noexcept { return Matrix{0, 0, 0}; }
bool Matrix_Type::Empty::Is(const Matrix &m) noexcept { return m.NumberLines() == 0 && m.NumberColumns() == 0; }
void Matrix_Type::Empty::To(Matrix &m) noexcept { m.Clear(); }

Matrix Matrix_Type::Null::Make(std::size_t x, std::size_t y) noexcept { return Matrix{x, y, 0}; }
bool Matrix_Type::Null::Is(const Matrix &m) noexcept { return m == Matrix_Type::Null::Make(m.NumberLines(), m.NumberColumns()); }
void Matrix_Type::Null::To(Matrix &m) noexcept { m = Matrix_Type::Null::Make(m.NumberLines(), m.NumberColumns()); }

Matrix Matrix_Type::Full::Make(std::size_t x, std::size_t y, int n) noexcept { return Matrix{x, y, n}; }
bool Matrix_Type::Full::Is(const Matrix &m) noexcept { return m.Empty() || m == Matrix{m.NumberLines(), m.NumberColumns(), m(0, 0)}; }
void Matrix_Type::Full::To(Matrix &m) noexcept { m = Matrix_Type::Full::Make(m.NumberLines(), m.NumberColumns(), m(0, 0)); }

Matrix Matrix_Type::Square::Make(std::size_t s, int n) noexcept { return Matrix{s, s, n}; }
bool Matrix_Type::Square::Is(const Matrix &m) noexcept { return m.NumberLines() == m.NumberColumns(); }

void Matrix_Type::Square::To(Matrix &m) noexcept {

    if (!Matrix_Type::Square::Is(m)) {

        if (m.NumberLines() > m.NumberColumns()) {

            m.RemoveLines(m.NumberLines()-m.NumberColumns());

        } else {

            m.RemoveColumns(m.NumberColumns()-m.NumberLines());

        }

    }

}

Matrix Matrix_Type::Unit::Make(std::size_t s) noexcept {

    Matrix m{Matrix_Type::Null::Make(s, s)};
    for (std::size_t i{0}; i < s; i++) m(i, i) = 1;

    return m;

}

bool Matrix_Type::Unit::Is(const Matrix &m) noexcept { return m == Matrix_Type::Unit::Make(m.NumberLines()); }

void Matrix_Type::Unit::To(Matrix &m) noexcept {
    
    Matrix_Type::Square::To(m);
    m = Matrix_Type::Unit::Make(m.NumberLines()); 

}

Matrix Matrix_Type::Diagonal::Make(std::size_t s, int n) noexcept {

    Matrix m{Matrix_Type::Square::Make(s, 0)};
    for (std::size_t i{0}; i < s; i++) m(i, i) = n;

    return m;

}

bool Matrix_Type::Diagonal::Is(const Matrix &m) noexcept { return m.Empty() || m == Matrix_Type::Diagonal::Make(m.NumberLines(), m(0, 0)); }
void Matrix_Type::Diagonal::To(Matrix &m) noexcept { m = Matrix_Type::Diagonal::Make(m.NumberLines(), m(0, 0)); }

Matrix Matrix_Type::UpTriangular::Make(std::size_t s, int n) noexcept {

    Matrix m{Matrix_Type::Diagonal::Make(s, n)};
    for (std::size_t x{0}; x < s; x++) {

        for (std::size_t y{0}; y < s; y++) {

            if (y > x) m(x, y) = n;

        }

    }

    return m;

}

bool Matrix_Type::UpTriangular::Is(const Matrix &m) noexcept { return m.Empty() || m == Matrix::MakeUpTriangular(m.NumberLines(), m(0, 0)); }

void Matrix_Type::UpTriangular::To(Matrix &m) noexcept {



}

Matrix Matrix_Type::LowTriangular::Make(std::size_t s, int n) noexcept {

    Matrix m{Matrix_Type::Diagonal::Make(s, n)};
    for (std::size_t x{0}; x < s; x++) {

        for (std::size_t y{0}; y < s; y++) {

            if (y < x) m(x, y) = n;

        }

    }

    return m;

}

bool Matrix_Type::LowTriangular::Is(const Matrix &m) noexcept { return m.Empty() || m == Matrix::MakeLowTriangular(m.NumberLines(), m(0, 0)); }

void Matrix_Type::LowTriangular::To(Matrix &m) noexcept {

    

}

Matrix Matrix_Type::Hollow::Make(std::size_t s, const Matrix &m) noexcept {

    Matrix hollow{Matrix_Type::Null::Make(s, s)};
    for (std::size_t x{0}; x < s; x++) {

        for (std::size_t y{0}; y < s; y++) {

            if (x != y && x < m.NumberLines() && y < m.NumberColumns()) hollow(x, y) = m(x, y);

        }

    }

    return hollow;

}

bool Matrix_Type::Hollow::Is(const Matrix &m) noexcept {

    if (!Matrix_Type::Square::Is(m)) return false;
    for (std::size_t i{0}; i < m.NumberLines(); i++) if (m(i, i) != 0) return false;

    return true;

}

void Matrix_Type::Hollow::To(Matrix &m) noexcept {



}

Matrix Matrix_Type::Sparse::Make(std::size_t) noexcept {



}

bool Matrix_Type::Sparse::Is(const Matrix&) noexcept {



}

void Matrix_Type::Sparse::To(Matrix&) noexcept {

    

}

Matrix Matrix_Type::Random::Make(std::size_t x, std::size_t y, int min, int max) {

    Matrix m{x, y};
    for (std::size_t i{0}; i < x; i++) {

        for (std::size_t j{0}; j < y; j++) m(i, j) = (min-1)+rand()%(max-min)+2;

    }

    return m;

}

bool Matrix_Type::Random::Is(const Matrix&) noexcept { return true; }
void Matrix_Type::Random::To(Matrix&) noexcept { return; }