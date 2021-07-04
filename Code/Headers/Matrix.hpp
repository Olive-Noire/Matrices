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

    void AddLines(std::vector<int> = {}, std::size_t = 1);
    void AddLines(std::size_t);
    void AddColumns(std::vector<int> = {}, std::size_t = 1);
    void AddColumns(std::size_t);

    void RemoveLines(std::size_t = 1);
    void RemoveColumns(std::size_t = 1);

    Matrix Transpose() const noexcept;

    bool Empty() const noexcept;
    void Clear() noexcept;
    void Reverse();

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

#endif // DEF_MATRIX_HPP