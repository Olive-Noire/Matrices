#ifndef DEF_MATRIX_HPP
#define DEF_MATRIX_HPP

#include <iosfwd>
#include <vector>

class Matrix {

    public:

    Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;

    Matrix(std::size_t, std::size_t, int = 0) noexcept;

    ~Matrix() = default;

    std::size_t NumberLines() const noexcept;
    std::size_t NumberColumns() const noexcept;

    std::vector<int> GetLine(std::size_t) const;
    std::vector<int> GetColumn(std::size_t) const;

    void AddLine(const std::vector<int>&);
    void AddColumn(const std::vector<int>&);

    void RemoveLine(std::size_t = 1);
    void RemoveColumn(std::size_t = 1);

    Matrix Transpose() const noexcept;

    bool Empty() const noexcept;
    void Clear() noexcept;
    void Reverse();

    static Matrix MakeNull(std::size_t) noexcept;
    static Matrix MakeSquare(std::size_t, int = 0) noexcept;
    static Matrix MakeUnit(std::size_t) noexcept;
    static Matrix MakeDiagonal(std::size_t, int) noexcept;
    static Matrix MakeUpTriangular(std::size_t, int = 1) noexcept;
    static Matrix MakeLowTriangular(std::size_t, int = 1) noexcept;
    static Matrix MakeHollow(std::size_t, const Matrix&) noexcept;

    bool IsNull() const noexcept;
    bool IsSquare() const noexcept;
    bool IsUnit() const noexcept;
    bool IsDiagonal() const noexcept;
    bool IsUpTriangular() const noexcept;
    bool IsLowTriangular() const noexcept;
    bool IsHollow() const noexcept;

    Matrix operator!() const;

    friend Matrix operator+(const Matrix&, const Matrix&);
    friend Matrix operator-(const Matrix&, const Matrix&);

    friend Matrix operator*(const Matrix&, const Matrix&);
    friend Matrix operator*(const Matrix&, int) noexcept;

    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);

    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(int) noexcept;

    friend bool operator==(const Matrix&, const Matrix&) noexcept;
    friend bool operator!=(const Matrix&, const Matrix&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Matrix&);

    const int& operator()(std::size_t, std::size_t) const;
    int& operator()(std::size_t, std::size_t);

    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) noexcept = default;

    private:

    std::size_t m_lines, m_columns;
    std::vector<int> m_content;

};

// git commit -m "Gestions de nouvelles exceptions + Ajouts de fonctions membres + Ajout de l'inverse d'un matrice carré de taille 2 et étant en entière + Expansion des fonctions membres remove + Ajouts des types de matrices (Null, Square, Unit, Diagonale, Upper triangular, Lower triangular, Hollow) avec leurs vérifications"

#endif // DEF_MATRIX_HPP