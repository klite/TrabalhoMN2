#ifndef ALGEBRALGORITHMS_H_
#define ALGEBRALGORITHMS_H_

#include "algebratypes.h"
#include <cstdio>
#define epsilon 0.00000001

double abs(double x) {
    if (x >= 0.0) return x;
    else return -x;
}

//not working yet hehe
matrix gauss_jordan_inverse (const matrix& m) {
    int iter = 0;
    assert(m.is_square());
    int n = m.n_rows();
    matrix a(m);
    matrix inv = matrix::identity(n);
    for (int i=0 ; i<n ; ++i) {
        double max_pivot = i;
        for (int j=0 ; j<n ; ++j) {
            if (a(j,i) >= a(max_pivot,i)) {
                max_pivot = j;
            }
        }
        a.swap_lines(i,max_pivot);
        inv.swap_lines(i,max_pivot);

        cout << "iter: " << iter++ << endl;
        a.print();

        double ratio = 1/a(i,i);
        a.multiply_line(ratio,i);
        inv.multiply_line(ratio,i);
        for (int j=0 ; j<n ; ++j) {
            if (j != i) {
                double c = m(j,i);
                a.sum_lines(-c,i,j);
                inv.sum_lines(-c,i,j);
                cout << "iter: " << iter++ << endl <<"c: " << c << endl;
                a.print();
            }
        }
    }
    a.print();
    inv.print();
    return inv;
}

bool is_accurate (const m_vector& a, const m_vector& b) {
    double max_diff = 0.0;
    double max_el   = 0.0;
    for (int i=0 ; i<a.size() ; ++i) {
        if (abs(a(i)-b(i)) > max_diff) max_diff = abs(a(i)-b(i));
        if (abs(a(i))>max_el) max_el = abs(a(i));
    }
    if (max_diff/max_el < epsilon) return true;
    else return false;
}

//this works
m_vector gauss_jacobi (matrix& a, m_vector& b, m_vector initial_guess) {
    assert(a.is_square() && a.n_rows() == b.size());
    int n = a.n_rows();
    m_vector d = initial_guess;
    m_vector e (n);
    int k=0;

    while (!is_accurate(d,e)) {
        e = d;
        for (int i=0 ; i<n ; ++i) {
            double sigma = 0;
            for (int j=0 ; j<n ; ++j) {
                if (j != i) {
                    sigma += a(i,j)*e(j);
                }
            }
            d(i) = (b(i)-sigma)/a(i,i);
            cout << "iter : " << k++ << endl;
            d.print();
        }
    }
    return d;
}

matrix iterative_inverse (matrix& a, m_vector(*solver)(matrix&,m_vector&,m_vector)) {
    assert(a.is_square());
    int n = a.n_rows();
    vector<m_vector> columns;
    m_vector iden_col(n);
    m_vector o(n);
    for (int i=0 ; i<n ; ++i) {
        iden_col(i) = 1;
        columns.push_back((*solver)(a,iden_col,o));
        iden_col(i) = 0;
    }
    return matrix(columns);
}

bool is_diagonally_dominant (matrix& a) {
	int i,j,n=a.n_rows();
	for (i=0;i<n;i++) {
		double s=0;
		for (j=0;j<n;j++) {
			if (j!=i) {
				s=abs(a(i,j))+s;
			}
		}
		s=s/abs(a(i,i));
		if (s>=1) {
			return 0;
		}
	}
	return 1;
}

//it is swaping only lines and it is not working properly yet // very much gambiarra and love <3
matrix fixed_matrix (matrix& a) {
	matrix aux=a;
    int errado=-1,i,j,n=a.n_rows();
	for (i=0;i<n;i++) {
		double s=0,maior=0;
		for (j=0;j<n;j++) {
			if (j!=i) {
				s=abs(a(i,j))+s;
			}
		}
		s=s/abs(a(i,i));
		if (s>=1) {
			for (int p=0;p<n;p++) {
				if (p!=i and p!=errado)
					for (int q=0;q<n;q++)
						if (aux(p,q)>maior)
							maior=aux(p,q);
				if (maior>aux(i,i))
					aux.swap_lines (i, p);
				if (!(is_diagonally_dominant(aux))) {
					errado=p;
				}
				else{
					return aux;
				}
			}
		}
	}
return a;
}

#endif //ALGEBRALGORITHMS_H_
