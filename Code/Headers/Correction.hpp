#include "./Matrix.hpp"

#ifndef DEF_MATRIX_HPP
#define DEF_MATRIX_HPP

#include <iosfwd>
#include <vector>

/**
 * @brief Manipulation de matrices.
 */
class Matrice
{
public:
    /**
     * @brief Créé une nouvelle instance de Matrice.
     * @param[in] lignes Le nombre de lignes de la matrice à créer.
     * @param[in] colonne Le nombre de colonnes de la matrice à créer.
     * @pre Le nombre de lignes et de colonnes doit être supérieur à 0.
     * @param[in] valeur_initiale La valeur à donner à chaque élément de la matrice. Vaut 0 par défaut.
     */
    Matrice(std::size_t lignes, std::size_t colonne, int valeur_initiale = 0);

    /**
     * @brief Constructeur de copie par défaut.
     * @param[in] matrice La matrice à copier.
     */
    Matrice(Matrice const & matrice) = default;

    /**
     * @brief Opérateur d'affectation par copie par défaut.
     * @param[in] matrice La matrice à copier.
     * @return La matrice actuelle après copie.
     */
    Matrice& operator=(Matrice const & matrice) = default;

    /**
     * @brief Opérateur d'accès à un élément de la matrice, version constante.
     * @param[in] x L'indice de la ligne voulue.
     * @param[in] y L'indice de la colonne voulue.
     * @pre Les indices de ligne et de colonne doivent être inférieurs aux dimensions de la matrice.
     * @return Une référence constante sur l'indice trouvé.
     */
    int const & operator()(std::size_t x, std::size_t y) const;

    /**
     * @brief Opérateur d'accès à un élément de la matrice.
     * @param[in] x L'indice de la ligne voulue.
     * @param[in] y L'indice de la colonne voulue.
     * @pre Les indices de ligne et de colonne doivent être inférieurs aux dimensions de la matrice.
     * @return Une référence sur l'indice trouvé.
     */
    int& operator()(std::size_t x, std::size_t y);

    /**
     * @brief Additionne une matrice à la matrice courante.
     * @param matrice La matrice à additionner à la matrice courante.
     * @pre La matrice passée en paramètre doit être de même dimension que la matrice courante.
     * @return Matrice& L'objet modifié après addition.
     */
    Matrice& operator+=(Matrice const & matrice);

    /**
     * @brief Opérateur libre d'addition de deux matrices.
     * @param[in] lhs La matrice de gauche. 
     * @param[in] rhs La matrice de droite.
     * @pre Les deux matrices doivent être de même dimension.
     * @return Le résultat de l'addition des deux matrices.
     */
    friend Matrice operator+(Matrice lhs, Matrice const & rhs);

    /**
     * @brief Multiplie la matrice courante par un entier.
     * @param[in] multiplicateur Un entier, par lequel la matrice est multipliée.
     * @return L'objet modifié après multiplication.
     */
    Matrice& operator*=(int multiplicateur);

    /**
     * @brief Opérateur libre de multiplication d'une matrice par un entier.
     * @param[in] m La matrice à multiplier.
     * @param[in] multiplicateur L'entier multiplicateur.
     * @return Le résultat de la multiplication d'une matrice par un entier.
     */
    friend Matrice operator*(Matrice m, int multiplicateur);

    /**
     * @brief Opérateur libre de multiplication d'une matrice par un entier.
     * @param[in] multiplicateur L'entier multiplicateur.
     * @param[in] m La matrice à multiplier.
     * @return Le résultat de la multiplication d'une matrice par un entier.
     */
    friend Matrice operator*(int multiplicateur, Matrice m);

    /**
     * @brief Multiplie la matrice courante par une autre matrice.
     * @param[in] matrice La matrice par laquelle la matrice courante sera multipliée.
     * @return L'objet modifié après multiplication.
     */
    Matrice& operator*=(Matrice const & matrice);

    /**
     * @brief Opérateur libre de multiplications de matrices.
     * @param[in] lhs La matrice de gauche.
     * @param[in] rhs La matrice de droite.
     * @return Le résultat de la multiplication d'une matrice par une autre.
     */
    friend Matrice operator*(Matrice const & lhs, Matrice const & rhs);

    /**
     * @brief Affiche une matrice sur un flux de sortie.
     * @param[in,out] stream Le flux sur lequel sera affichée la matrice.
     * @param[in] matrice La matrice à afficher.
     * @return Le flux de sortie utilisé.
     */
    friend std::ostream& operator<<(std::ostream & stream, Matrice const & matrice);
    
    /**
     * @brief Retourne un vecteur ligne, selon l'indice demandé.
     * @param[in] index_ligne L'index de la ligne désirée.
     * @pre L'index de la ligne désirée doit être strictement inférieur au nombre de lignes de la matrice.
     * @return Un vecteur ligne de type Matrice, correspondant à la ligne demandée.
     */
    Matrice ligne(std::size_t index_ligne) const;

    /**
     * @brief Retourne un vecteur colonne, selon l'indice demandé.
     * @param[in] index_colonne L'index de la colonne désirée.
     * @pre L'index de la colonne désirée doit être strictement inférieur au nombre de colonnes de la matrice.
     * @return Un vecteur colonne de type Matrice, correspondant à la colonne demandée.
     */
    Matrice colonne(std::size_t index_colonne) const;

    /**
     * @brief Transpose la matrice courante.
     * @return La matrice courante une fois transposée.
     */
    Matrice transpose() const;

    /**
     * @brief Donne le nombre de lignes de la matrice actuelle.
     * @return Le nombre de lignes de la matrice actuelle.
     */
    std::size_t nb_lignes() const noexcept;

    /**
     * @brief Donne le nombre de colonnes de la matrice actuelle.
     * @return Le nombre de colonnes de la matrice actuelle.
     */
    std::size_t nb_colonnes() const noexcept;

private:
    /**
     * Permet de calculer la position dans le tableau de l'élement qui se trouve à la ligne et à la colonne demandées.
     * @param[in] ligne La ligne demandée.
     * @param[in] colonne La colonne demandée.
     * @pre La ligne et la colonne doivent être inférieures aux dimensions de la matrice.
     * @returns L'index dans le tableau auquel se trouve l'élément.
     */ 
    std::size_t offset(std::size_t ligne, std::size_t colonne) const noexcept;

    std::size_t m_nb_lignes;
    std::size_t m_nb_colonnes;
    std::vector<int> m_matrice;
};

#endif