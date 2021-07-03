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

    std::vector<int> GetLine(std::size_t) const noexcept;
    std::vector<int> GetColumn(std::size_t) const noexcept;

    void AddLine(const std::vector<int>&);
    void AddColumn(const std::vector<int>&);

    void RemoveLine();
    void RemoveColumn();

    Matrix Transpose() const noexcept;

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

    std::vector<std::vector<int>> m_content;

};

#endif // DEF_MATRIX_HPP