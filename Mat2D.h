#ifndef MAT2D_H
#define MAT2D_H

#include <iostream>
#include <vector>

template <class T>
class Mat2D
{
    private:

        size_t m_cols;
        size_t m_rows;
        unsigned int m_ghosts;
        std::vector<T> mat = {};

    public:

    Mat2D(size_t cols, size_t rows, unsigned int ghosts) : m_cols(cols), m_rows(rows), m_ghosts(ghosts)
    {
        size_t length = (m_cols + 2*m_ghosts)*(m_rows + 2*m_ghosts);
        mat.reserve(length*sizeof(T));
    }

    const T& operator()(size_t i,size_t j) const
    {
        size_t jump = m_cols + 2*m_ghosts;
        return mat[ (i+m_ghosts) + (j+m_ghosts)*jump ];
    }

    T& operator()(size_t i,size_t j)
    {
        size_t jump = m_cols + 2*m_ghosts;
        return mat[ (i+m_ghosts) + (j+m_ghosts)*jump ];
    }

    unsigned int getGhost() const {return m_ghosts;}

};

#endif // MAT2D_H
