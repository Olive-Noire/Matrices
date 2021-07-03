#ifndef DEF_MATRICE_HPP
#define DEF_MATRICE_HPP

#include <iosfwd>
#include <vector>

class Matrice {

    public:

    Matrice() = default;
    Matrice(const Matrice&) = default;
    Matrice(Matrice&&) noexcept = default;

    Matrice(std::size_t, std::size_t, int = 0) noexcept;

    ~Matrice() = default;

    std::size_t NumberLines() const noexcept;
    std::size_t NumberColumns() const noexcept;

    std::vector<int> GetLine(std::size_t) const noexcept;
    std::vector<int> GetColumn(std::size_t) const noexcept;

    void AddLine(const std::vector<int>&);
    void AddColumn(const std::vector<int>&);

    void RemoveLine();
    void RemoveColumn();

    Matrice Transpose() const noexcept;

    friend Matrice operator+(const Matrice&, const Matrice&);

    friend Matrice operator*(const Matrice&, const Matrice&);
    friend Matrice operator*(const Matrice&, int) noexcept;

    Matrice& operator+=(const Matrice&);

    Matrice& operator*=(const Matrice&);
    Matrice& operator*=(int) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Matrice&);

    const int& operator()(std::size_t, std::size_t) const noexcept;
    int& operator()(std::size_t, std::size_t) noexcept;

    Matrice& operator=(const Matrice&) = default;
    Matrice& operator=(Matrice&&) noexcept = default;

    private:

    std::vector<std::vector<int>> m_content;

};

int ScalarCalcul(const std::vector<int>&, const std::vector<int>&);

#endif // DEF_MATRICE_HPP