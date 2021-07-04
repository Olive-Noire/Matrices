#ifndef DEF_MATRIX_TYPES_HPP
#define DEF_MATRIX_TYPES_HPP

#include <cstdlib>

#include "./Matrix.hpp"

namespace Matrix_Type {

    namespace Empty {

        Matrix Make() noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Null {

        Matrix Make(std::size_t, std::size_t) noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Full {

        Matrix Make(std::size_t, std::size_t, int = 1) noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Square {

        Matrix Make(std::size_t, int = 0) noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Unit {

        Matrix Make(std::size_t) noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Diagonal {

        Matrix Make(std::size_t, int) noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace UpTriangular {

        Matrix Make(std::size_t, int = 1) noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace LowTriangular {

        Matrix Make(std::size_t, int = 1) noexcept;
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Hollow {

        Matrix Make(std::size_t, int = -(RAND_MAX/2), int = RAND_MAX/2);
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Symetric {

        Matrix Make(std::size_t, int = -(RAND_MAX/2), int = RAND_MAX/2);
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

    namespace Sparse {

        Matrix Make(std::size_t, std::size_t, int = -(RAND_MAX/2), int = RAND_MAX/2);
        bool Is(const Matrix&) noexcept;
        void To(Matrix&);

    }

    namespace Random {

        Matrix Make(std::size_t, std::size_t, int = -RAND_MAX/2, int = RAND_MAX/2);
        bool Is(const Matrix&) noexcept;
        void To(Matrix&) noexcept;

    }

}

#endif // DEF_MATRIX_TYPES_HPP