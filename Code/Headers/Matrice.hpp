#ifndef DEF_MATRICE_HPP
#define DEF_MATRICE_HPP

#include <ostream>
#include <vector>

class Matrice {

    public:

    Matrice(const Matrice&) = default;
    Matrice(Matrice&&) noexcept = default;

    Matrice(std::size_t, std::size_t) noexcept;

    ~Matrice() = default;

    std::size_t Lines() const noexcept;
    std::size_t Columns() const noexcept;

    Matrice Transpose() const noexcept;

    friend Matrice operator+(const Matrice&, const Matrice&) noexcept;

    friend Matrice operator*(const Matrice&, const Matrice&) noexcept;
    friend Matrice operator*(const Matrice&, int) noexcept;

    Matrice& operator+=(const Matrice&) noexcept;

    Matrice& operator*=(const Matrice&) noexcept;
    Matrice& operator*=(int) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Matrice&);

    int& operator()(std::size_t, std::size_t) const;
    int& operator()(std::size_t, std::size_t);

    Matrice& operator=(const Matrice&) = default;
    Matrice& operator=(Matrice&&) noexcept = default;

    private:

    std::vector<int> m_content;

};

#endif // DEF_MATRICE_HPP