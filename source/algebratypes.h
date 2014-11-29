#ifndef ALGEBRATYPES_H_
#define ALGEBRATYPES_H_

#include <initializer_list>
#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;
class m_vector;
class matrix;

//---------------------matrix class----------------------------

class matrix {
    public :

        //constructors
        matrix (int,int);
        matrix (const matrix&);
        matrix (std::initializer_list<m_vector>);
        matrix (std::vector<m_vector>);


        //destructor
        ~matrix (void);

        static matrix identity (int n) {
            matrix identity(n,n);
            for (int i=0 ; i < n; i++) identity(i,i) = 1;
                return identity;
        }

        //functions
        double* line (int);
        double& at (int,int) const; //at(i,j)++ ou at(i,j) = 0.0
        void print (void); //matrix m; m[i][j];
        matrix transpose (void);

        //getters and properties
        inline int n_rows (void) const;
        inline int n_columns (void) const;
        inline bool is_square (void) const;

        //access operators
        inline double* operator[] (int);
        inline double& operator() (int,int) const;

        //line operations
        void sum_lines (double,int,int);
        void swap_lines (int,int);
        void multiply_line (double,int);


    protected :

        double** m;
        int r, c;

};

//returns the ith line
inline double* matrix::line (int l) {
    if (l < r) return m[l];
    return nullptr;
}

//accessing an element
inline double& matrix::at (int i, int j) const {
    assert(i < r && j < c);
    return m[i][j];
}

inline int matrix::n_rows () const { return r; }

inline int matrix::n_columns () const { return c; }

inline bool matrix::is_square () const { return (r == c); }

//overload for the line(int) method so one can use M[i][j] to access the matrix elements
inline double* matrix::operator[] (int i) { return line(i); }

//overload for the at(int,int) method so one can use M(i,j) to access the matrix elements
inline double& matrix::operator() (int i, int j) const {
    return at(i,j);
}

//matrix sum
matrix operator+ (const matrix&, const matrix&);

//matrix product
matrix operator* (const matrix&, const matrix&);

//puts the diagonal of a in d. Puts the rest of a in r
void divide_matrix (const matrix&, const matrix&, matrix&);

double determinant (matrix&);

//------------------m_vector class--------------------------

class m_vector {
    public :
        //constructors
        m_vector (int);
        m_vector (const m_vector&);
        m_vector (std::initializer_list<double>);

        //destructor
        ~m_vector (void);

        double* to_array (void);

        double& operator[] (int) const;
        double& operator() (int) const;

        m_vector& operator= (const m_vector&);
        m_vector& operator+= (const m_vector&);
        m_vector& operator-= (const m_vector&);

        int size (void) const;
        matrix transpose (void);
        void print (void);

    private :

        double* v;
        int sz;

};

inline double& m_vector::operator[] (int i) const { return v[i]; }

inline double& m_vector::operator() (int i) const {
    assert(i >= 0 && i < sz);
    return v[i];
}

inline m_vector& m_vector::operator= (const m_vector& a) {
    for (int i=0 ; i<a.size() && i<size() ; ++i) {
        v[i] = a(i);
    }
    return *this;
}

inline m_vector operator* (const matrix& M, const m_vector& vec) {
    assert(vec.size() == M.n_columns());
    int n = M.n_rows();
    int m = vec.size();
    m_vector prod(n);
    for (int i=0 ; i<n ; ++i) {
        for (int j=0 ; j<m ; ++j) {
            prod(i) += vec(j) * M(i,j);
        }
    }
    return prod;
}

#endif //ALGEBRA_TYPES
