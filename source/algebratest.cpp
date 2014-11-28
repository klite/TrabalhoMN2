#include "algebratypes.h"
#include "algebralgorithms.h"

int main () {
    m_vector c1 {10,1,2};
    m_vector c2 {2,5,3};
    m_vector c3 {1,1,10};

    matrix a {c1,c2,c3};
    m_vector b {7,-8,6};

    gauss_jacobi(a,b,m_vector{0.95,-1.75,0.95}).print();

    return 0;
}
