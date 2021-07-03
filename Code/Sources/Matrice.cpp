#include "../Headers/Matrice.hpp"

#include <stdexcept>

Matrice::Matrice(std::size_t x, std::size_t y) noexcept : m_content(x, std::vector(y, 0)) {}

std::size_t Matrice::Lines() const noexcept { return m_content.size(); }
std::size_t Matrice::Columns() const noexcept { return m_content[0].size(); }

Matrice Matrice::Transpose() const noexcept {

    Matrice t{Columns(), Lines()};
    for (std::size_t x{0}; x < Lines(); x++) {
        
        for(std::size_t y{0}; y < Columns(); y++) t(y, x) = this->operator()(x, y);

    }

    return t;

}

Matrice operator+(const Matrice &l, const Matrice &r) {

    if (l.Lines() == r.Lines() && l.Columns() == r.Columns()) {

        Matrice t{l};
        for (std::size_t x{0}; x < t.Lines(); x++) {

            for (std::size_t y{0}; y < t.Columns(); y++) t(x, y) += r(x, y);

        }

        return t;

    } else throw std::runtime_error{"Error : Matrices dimensions does not equals"};

}

Matrice operator*(const Matrice &l, const Matrice &r) {

    if (l.Columns() == r.Lines()) {

        Matrice result{l.Lines(), r.Columns()};

        for (std::size_t x{0}; x < l.Lines(); x++) {

            for (std::size_t y{0}; y < r.Columns(); y++) {

                result(x, y) = ScalarCalcul(l.m_content[x], r.Transpose().m_content[y]);

            }

        }

        return result;

    } else throw std::runtime_error{"Error : Matrices dimensions does not equals"};

}

Matrice operator*(const Matrice &m, int n) noexcept {

    Matrice t{m};
    for (std::size_t x{0}; x < t.Lines(); x++) {

        for (std::size_t y{0}; y < t.Columns(); y++) t(x, y) *= n;

    }

    return t;

}

Matrice& Matrice::operator+=(const Matrice &m) {

    *this = *this+m;
    return *this;

}

Matrice& Matrice::operator*=(const Matrice &m) {

    *this = *this*m;
    return *this;

}

Matrice& Matrice::operator*=(int n) noexcept {

    *this = *this*n;
    return *this;

}

std::ostream& operator<<(std::ostream &flux, const Matrice &m) {

    for (std::size_t x{0}; x < m.Lines(); x++) {

        for (std::size_t y{0}; y < m.Columns(); y++) flux << m(x, y) << ' ';
        flux << std::endl;

    }

    return flux;

}

const int& Matrice::operator()(std::size_t x, std::size_t y) const noexcept { return m_content[x][y]; }
int& Matrice::operator()(std::size_t x, std::size_t y) noexcept { return m_content[x][y]; }

int ScalarCalcul(const std::vector<int> &line, const std::vector<int> &column) {

    if (line.size() == column.size()) {

        int result{0};
        for (std::size_t i{0}; i < line.size(); i++) result += line[i]*column[i];

        return result;

    } else throw std::runtime_error{"Error : Scalar-vectors sizes does not equals"};

}

/*

CORRECTION:

#include <algorithm>
#include <cassert>
#include <ostream>
#include <numeric>
#include "Matrice.hpp"

Matrice::Matrice(std::size_t lignes, std::size_t colonnes, int valeur_initiale)
  : m_nb_lignes(lignes), m_nb_colonnes(colonnes), m_matrice(lignes * colonnes, valeur_initiale)
{
    assert(m_nb_lignes > 0 && m_nb_colonnes > 0 && "On ne peut pas avoir une matrice de dimension 0.");
}

std::size_t Matrice::offset(std::size_t ligne, std::size_t colonne) const noexcept
{
    assert(ligne < m_nb_lignes && "Ligne demandée invalide.");
    assert(colonne < m_nb_colonnes && "Colonne demandée invalide.");
    return colonne * m_nb_lignes + ligne;
}

int const & Matrice::operator()(std::size_t x, std::size_t y) const
{
    return m_matrice[offset(x, y)];
}

int& Matrice::operator()(std::size_t x, std::size_t y)
{
    return m_matrice[offset(x, y)];
}

Matrice& Matrice::operator+=(Matrice const & matrice)
{
    assert(nb_lignes() == matrice.nb_lignes() && nb_colonnes() == matrice.nb_colonnes() && "Impossible d'additionner deux matrices de dimensions différentes.");
    for (std::size_t i { 0 }; i < nb_lignes(); ++i)
    {
        for (std::size_t j { 0 }; j < nb_colonnes(); ++j)
        {
            (*this)(i, j) += matrice(i, j);
        }
    }
    return *this;
}

Matrice operator+(Matrice lhs, Matrice const & rhs)
{
    lhs += rhs;
    return lhs;
}

Matrice& Matrice::operator*=(int multiplicateur)
{
    for (std::size_t i { 0 }; i < nb_lignes(); ++i)
    {
        for (std::size_t j { 0 }; j < nb_colonnes(); ++j)
        {
            (*this)(i, j) *= multiplicateur;
        }
    }
    return *this;
}

Matrice operator*(Matrice matrice, int multiplicateur)
{
    matrice *= multiplicateur;
    return matrice;
}

Matrice operator*(int multiplicateur, Matrice matrice)
{
    return matrice * multiplicateur;
}

Matrice& Matrice::operator*=(Matrice const & matrice)
{
    Matrice copie { *this * matrice };
    std::swap(*this, copie);
    return *this; 
}

Matrice operator*(Matrice const & lhs, Matrice const & rhs)
{
    assert(lhs.nb_colonnes() == rhs.nb_lignes() && "Le nombre de colonnes de la matrice multipliée doit être égal au nombre de lignes de la matrice multipliante.");

    Matrice copie { lhs.nb_lignes(), rhs.nb_colonnes() };
    for (std::size_t i { 0 }; i < copie.nb_lignes(); ++i)
    {
        auto const ligne_courante { lhs.ligne(i).m_matrice };
        for (std::size_t j { 0 }; j < copie.nb_colonnes(); ++j)
        {
            auto const colonne_courante { rhs.colonne(j).m_matrice };
            const int valeur { std::inner_product(std::begin(ligne_courante), std::end(ligne_courante), std::begin(colonne_courante), 0) };
            copie(i, j) = valeur;
        }
    }

    return copie;
}

std::ostream& operator<<(std::ostream & stream, Matrice const & matrice)
{
    for (std::size_t i { 0 }; i < matrice.nb_lignes(); ++i)
    {
        for (std::size_t j { 0 }; j < matrice.nb_colonnes(); ++j)
        {
            stream << matrice(i, j) << " ";
        }
        stream << "\n";
    }
    return stream;
}

Matrice Matrice::ligne(std::size_t index_ligne) const
{
    assert(index_ligne < nb_lignes() && "L'index demandé pour la ligne est plus grand que la dimension de la matrice.");

    Matrice matrice_ligne { 1, nb_colonnes() };
    for (std::size_t j { 0 }; j < nb_colonnes(); ++j)
    {
        matrice_ligne(0, j) = (*this)(index_ligne, j);
    }
    return matrice_ligne;
}

Matrice Matrice::colonne(std::size_t index_colonne) const
{
    assert(index_colonne < nb_colonnes() && "L'index demandé pour la colonne est plus grand que la dimension de la matrice.");

    Matrice matrice_colonne { nb_lignes(), 1 };
    for (std::size_t i { 0 }; i < nb_lignes(); ++i)
    {
        matrice_colonne(i, 0) = (*this)(i, index_colonne);
    }
    return matrice_colonne;
}

Matrice Matrice::transpose() const
{
    Matrice transposee { nb_colonnes(), nb_lignes() };
    for (std::size_t i { 0 }; i < nb_lignes(); ++i)
    {
        for (std::size_t j { 0 }; j < nb_colonnes(); ++j)
        {
            transposee(j, i) = (*this)(i, j);
        }
    }

    return transposee;
}

std::size_t Matrice::nb_lignes() const noexcept
{
    return m_nb_lignes;
}

std::size_t Matrice::nb_colonnes() const noexcept
{
    return m_nb_colonnes;
}

*/