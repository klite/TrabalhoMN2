#include "algebratypes.h"

//-----------------------matrix functions---------------------------

//Dinamically allocates the underlying 2d array
matrix::matrix (int r_arg, int c_arg) {
    m = new double*[r_arg];
    for (int i=0 ; i<r_arg ; ++i) m[i] = new double[c_arg];
    for (int i=0 ; i<r_arg ; ++i) for (int j=0 ; j<c_arg ; ++j) m[i][j] = 0;
    r = r_arg;
    c = c_arg;
}

//copy constructor
matrix::matrix (const matrix& M) {
    int n_rows    = M.n_rows();
    int n_columns = M.n_columns();
    m = new double*[n_rows];
    for (int i=0 ; i<n_rows ; ++i) m[i] = new double[n_columns];
    for (int i=0 ; i<n_rows ; ++i) for (int j=0 ; j<n_columns ; ++j) m[i][j] = M(i,j);
    r = n_rows;
    c = n_columns;
}

matrix::matrix (std::initializer_list<m_vector> l) {
    int n_columns = l.size();
    int n_rows    = 0;

    for (const auto& v : l)
        if (v.size() > n_rows) n_rows = v.size();

    m = new double*[n_rows];
    for (int i=0 ; i<n_rows ; ++i) m[i] = new double[n_columns];

    int j = 0;

    for (const auto& v : l) {
        for (int i=0 ; i<v.size() ; ++i) m[i][j] = v(i);
        for (int i=v.size() ; i<n_rows ; ++i) m[i][j] = 0;
        j++;
    }
    r = n_rows;
    c = n_columns;
}

matrix::matrix (std::vector<m_vector> l) {
    int n_columns = l.size();
    int n_rows    = 0;

    for (const auto& v : l)
        if (v.size() > n_rows) n_rows = v.size();

    m = new double*[n_rows];
    for (int i=0 ; i<n_rows ; ++i) m[i] = new double[n_columns];

    int j = 0;

    for (const auto& v : l) {
        for (int i=0 ; i<v.size() ; ++i) m[i][j] = v(i);
        for (int i=v.size() ; i<n_rows ; ++i) m[i][j] = 0;
        j++;
    }
    r = n_rows;
    c = n_columns;
}

//deletes the underlying 2d array
matrix::~matrix () {
    for (int i=0 ; i < r ; ++i) delete []  m[i];
    delete [] m;
}

matrix operator+ (const matrix &A, const matrix &B) {
    assert (A.n_rows() == B.n_rows() && A.n_columns() == B.n_columns());
    int n = A.n_rows();
    int m = B.n_columns();
    matrix sum(n,m);
    for (int i=0 ; i<n ; ++i) {
        for (int j=0 ; j<m ; ++j) {
            sum(i,j) = A(i,j) + B(i,j);
        }
    }
    return sum;
};

//matrix product
matrix operator* (const matrix& a, const matrix& b) {
    assert (a.n_columns() == b.n_rows());
    int o = a.n_columns();
    int n = a.n_rows();
    int m = b.n_columns();
    matrix prod(n,m);
    for (int i=0 ; i<n ; i++) {
        for (int j=0 ; j<m ; j++) {
            for (int k=0 ; k<o ; ++k) {
                prod(i,j) += a(i,k)*b(k,j);
            }
        }
    }
    return prod;
}

matrix matrix::transpose () {
    matrix transpose(c,r);
    for (int i=0 ; i<r ; ++i)
        for (int j=0 ; j<c ; ++j)
            transpose(i,j) = m[j][i];

    return transpose;
}

void matrix::print () {
    for (int i=0 ; i<r ; ++i) {
        std::cout << "| ";
        for (int j=0 ; j<c ; ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << "|\n";
    }
}

void divide_matrix (const matrix& a, const matrix& b, const matrix& c) {
    //TODO
}

double determinant (const matrix& a) {
    //TODO

    return 0.0;
}

void matrix::sum_lines (double c, int i, int j) {
    if (i<0 || i>=r || j<0 || j >=r) return;
    for (int k=0 ; k<this->c ; ++k) m[j][k] += c * m[i][k];
}

void matrix::swap_lines (int i, int j) {
    if (i<0 || i>=r || j<0 || j >=r) return;
    auto aux = m[i];
    m[i] = m[j];
    m[j] = aux;
}

void matrix::multiply_line (double c, int i) {
    if (i<0 || i>=r) { cout << "fora\n"; return; }
    for (int k=0 ; k<this->c ; ++k) { m[i][k] *= c; }
}

//----------------------m_vector functions-----------------------

m_vector::m_vector (int n) {
    v = new double[n];
    for (int i=0 ; i<n ; i++) v[i] = 0;
    sz = n;
}

m_vector::m_vector (const m_vector& m) {
    v = new double[m.size()];
    sz = m.size();
    for (int i=0 ; i<sz ; i++) v[i] = m(i);
}

m_vector::m_vector (initializer_list<double> l) {
    int i = 0;
    v = new double[l.size()];
    sz = l.size();
    for (double x : l) v[i++] = x;
}

m_vector::~m_vector () {
    delete[] v;
}

double* m_vector::to_array () {
    double* arr = new double[sz];
    for (int i=0 ; i< sz ; ++i) arr[i] = v[i];
    return arr;
}

m_vector& m_vector::operator+= (const m_vector& a) {
    int n = a.size();
    int m =   size();
    for (int i=0 ; i<n && i<m ; ++i) this->v[i] += a(i);
    return *this;
}

m_vector& m_vector::operator-= (const m_vector& a) {
    int n = a.size();
    int m =   size();
    for (int i=0 ; i<n && i<m ; ++i) this->v[i] -= a[i];
    return *this;
}

matrix m_vector::transpose () {
    matrix m(1,sz);
    for (int i=0 ; i<sz ; ++i) m(0,i) = v[i];
    return m;
}

int m_vector::size () const { return sz; }

void m_vector::print () {
    for (int i=0 ; i<sz ; ++i)
        cout << "| " << v[i] << " |" <<endl;
}
