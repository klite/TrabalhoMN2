#include "algebratypes.h"
#include "algebralgorithms.h"

int main () {
    m_vector c1 {10,1,2};
    m_vector c2 {2,5,3};
    m_vector c3 {1,1,10};

    matrix a {c1,c2,c3};
    m_vector b {7,-8,6};

    matrix inv = iterative_inverse(a,gauss_jacobi);

    cout << "-------------\n";

    inv.print();

    cout << "-------------\n";

    vector<m_vector> columns;
    columns.push_back(c1);
    columns.push_back(c2);
    columns.push_back(c3);

    matrix a1 (columns);

    a1.print();
    cout << "hehe\n";

    (a*inv).print();

    return 0;
}
