#include "bezierBasis.h"
#include <iostream>
#include <fstream>
 

 

void bezierBasisRaiser::computeCoeff(fullVector<double>& coeffA,
    fullVector<double>& coeffB,
    fullVector<double>& coeffSquare) 
{
    coeffSquare.resize(_raiser2.size(), true);

    if (&coeffA == &coeffB) {
        for (std::size_t ind = 0; ind < _raiser2.size(); ++ind) {
            for (std::size_t l = 0; l < _raiser2[ind].size(); ++l) {
                const _data& d = _raiser2[ind][l];
                coeffSquare(ind) += d.val * coeffA(d.i) * coeffB(d.j);
            }
        }
    }
    else {
        for (std::size_t ind = 0; ind < _raiser2.size(); ++ind) {
            for (std::size_t l = 0; l < _raiser2[ind].size(); ++l) {
                const _data& d = _raiser2[ind][l];
                coeffSquare(ind) +=
                    d.val / 2 * (coeffA(d.i) * coeffB(d.j) + coeffA(d.j) * coeffB(d.i));
            }
        }
    }
}

void bezierBasisRaiser::computeCoeff( fullVector<double>& coeffA,
    fullVector<double>& coeffB,
     fullVector<double>& coeffC,
    fullVector<double>& coeffCubic) 
{
    coeffCubic.resize(_raiser3.size(), true);

    if (&coeffA == &coeffB && &coeffB == &coeffC) {
        for (std::size_t ind = 0; ind < _raiser3.size(); ++ind) {
            for (std::size_t l = 0; l < _raiser3[ind].size(); ++l) {
                const _data& d = _raiser3[ind][l];
                coeffCubic(ind) += d.val * coeffA(d.i) * coeffB(d.j) * coeffC(d.k);
            }
        }
    }
    else if (&coeffA != &coeffB && &coeffB != &coeffC) {
        for (std::size_t ind = 0; ind < _raiser3.size(); ++ind) {
            for (std::size_t l = 0; l < _raiser3[ind].size(); ++l) {
                const _data& d = _raiser3[ind][l];
                coeffCubic(ind) += d.val / 6 *
                    (coeffA(d.i) * coeffB(d.j) * coeffC(d.k) +
                        coeffA(d.i) * coeffB(d.k) * coeffC(d.j) +
                        coeffA(d.j) * coeffB(d.i) * coeffC(d.k) +
                        coeffA(d.j) * coeffB(d.k) * coeffC(d.i) +
                        coeffA(d.k) * coeffB(d.i) * coeffC(d.j) +
                        coeffA(d.k) * coeffB(d.j) * coeffC(d.i));
            }
        }
    }
    else
        printf(
            "bezierBasisRaiser::computeCoeff not implemented for A == B != C "
            "or A != B == C");

   


}


void bezierBasis::_construct()
{
    int order = _order;


    generateExponents(order, _exponents);






}

void bezierBasisRaiser::_fillRaiserData()
{
    // Let f and g be two function whose Bezier coefficients f_i, g_i are
  // given and let F = f*g. The B¨¦zier coefficients of F can be computed as
  // F_i = sum_(j,k) a_jk f_j * g_k
  // This function compute the coefficients a_jk (and similarly for 3 functions)
    fullMatrix<int> exp;
    {
        const fullMatrix<double>& expD = _bfs->_exponents; 
        double2int(expD, exp);
    }

    int order = _bfs->getOrder(); 
    int ncoeff = exp.size1(); 
    int dim = _bfs->getDim(); 
    int dimSimplex = _bfs->getDimSimplex(); 

    // Speedup: Since the coefficients (num/den) are invariant from a permutation
  // of the indices (i, j) or (i, j, k), we fill only the raiser data for
  // i <= j <= k (and adapt the value to take into account the multiplicity).

  // Construction of raiser 2
    std::map<int, int> hashToInd2;
    {
        fullMatrix<int> exp2;
        {
            fullMatrix<double> expD2;
            generateExponents(2 * order, expD2); 
            double2int(expD2, exp2); 
            _raiser2.resize(exp2.size1()); 
        }

        for (int i = 0; i < exp2.size1(); ++i) {
            int hash = 0;
            for (int l = 0; l < dim; l++) {
                //hash += static_cast<int>(exp2(i, l) * pow_int(2 * order + 1, l));
                hash += static_cast<int>(exp2(i, l) * std::pow(2 * order + 1, l));
            }
            hashToInd2[hash] = i;
        }
    }

    for (int i = 0; i < ncoeff; i++) {
        for (int j = i; j < ncoeff; j++) {
            double num = 1, den = 1;
            {
                int compl1 = order;
                int compl2 = order;
                int compltot = 2 * order;
                for (int l = 0; l < dimSimplex; l++) {
                    num *= nChoosek(compl1, exp(i, l)) * nChoosek(compl2, exp(j, l));
                    den *= nChoosek(compltot, exp(i, l) + exp(j, l));
                    compl1 -= exp(i, l);
                    compl2 -= exp(j, l);
                    compltot -= exp(i, l) + exp(j, l);
                }
                for (int l = dimSimplex; l < dim; l++) {
                    num *= nChoosek(order, exp(i, l)) * nChoosek(order, exp(j, l));
                    den *= nChoosek(2 * order, exp(i, l) + exp(j, l));
                }
            }

            // taking into account the multiplicity (reminder: i <= j)
            if (i < j) num *= 2;

            int hash = 0;
            for (int l = 0; l < dim; l++) {
                hash +=
                    //static_cast<int>((exp(i, l) + exp(j, l)) * pow_int(2 * order + 1, l));
                    static_cast<int>((exp(i, l) + exp(j, l)) * std::pow(2 * order + 1, l));
            }
            _raiser2[hashToInd2[hash]].push_back(_data(num / den, i, j));
        }
    }

    // Construction of raiser 3

    std::map<int, int> hashToInd3;
    {
        fullMatrix<int> exp3;
        {
            fullMatrix<double> expD3;
            generateExponents(3 * order, expD3); 
            double2int(expD3, exp3);
            _raiser3.resize(exp3.size1()); 
        }

        for (int i = 0; i < exp3.size1(); ++i) {
            int hash = 0;
            for (int l = 0; l < dim; l++) {
                hash += static_cast<int>(exp3(i, l) * std::pow(3 * order + 1, l));
            }
            hashToInd3[hash] = i;
        }
    }

    for (int i = 0; i < ncoeff; i++) {
        for (int j = i; j < ncoeff; j++) {
            for (int k = j; k < ncoeff; ++k) {
                double num = 1, den = 1;
                {
                    int compl1 = order;
                    int compl2 = order;
                    int compl3 = order;
                    int compltot = 3 * order;
                    for (int l = 0; l < dimSimplex; l++) {
                        num *= nChoosek(compl1, exp(i, l)) * nChoosek(compl2, exp(j, l)) *
                            nChoosek(compl3, exp(k, l));
                        den *= nChoosek(compltot, exp(i, l) + exp(j, l) + exp(k, l));
                        compl1 -= exp(i, l);
                        compl2 -= exp(j, l);
                        compl3 -= exp(k, l);
                        compltot -= exp(i, l) + exp(j, l) + exp(k, l);
                    }
                    for (int l = dimSimplex; l < dim; l++) {
                        num *= nChoosek(order, exp(i, l)) * nChoosek(order, exp(j, l)) *
                            nChoosek(order, exp(k, l));
                        den *= nChoosek(3 * order, exp(i, l) + exp(j, l) + exp(k, l));
                    }
                }

                // taking into account the multiplicity (Reminder: i <= j <= k)
                if (i < j && j < k)
                    num *= 6;
                else if (i < j || j < k)
                    num *= 3;

                int hash = 0;
                for (int l = 0; l < dim; l++) {
                    hash += static_cast<int>((exp(i, l) + exp(j, l) + exp(k, l)) *
                        std::pow(3 * order + 1, l));
                }
                _raiser3[hashToInd3[hash]].push_back(_data(num / den, i, j, k));
            }
        }
    }

}

void double2int(const fullMatrix<double>& matDouble, fullMatrix<int>& matInt)
{
    matInt.resize(matDouble.size1(), matDouble.size2());
    for (int i = 0; i < matDouble.size1(); ++i) {
        for (int j = 0; j < matDouble.size2(); ++j) {
            matInt(i, j) = static_cast<int>(matDouble(i, j) + .5);
        }
    }
}

// Exponents:
void generateExponents(int order,fullMatrix<double>& exp)
{
    
    gmshGenerateOrderedMonomials(order,exp);
}

void gmshGenerateOrderedMonomials(int order,fullMatrix<double>& monomials)
{
    int idx;
    monomials.resize((order + 1) * (order + 2) * (order + 3) / 6, 3);//TYPE_TET
    idx = 0;
    for (int k = 0; k < order + 1; ++k) {
        for (int j = 0; j < order + 1 - k; ++j) {
            for (int i = 0; i < order + 1 - j - k; ++i) {
                monomials(idx, 0) = i;
                monomials(idx, 1) = j;
                monomials(idx, 2) = k;
                ++idx;
            }
        }
    }
    return;
}

 
bezierBasis::bezierBasis(int order)
{
    _dimSimplex = 3;//TYPE_TET
    _order = order;
    _construct();
}

// Matrices generation
int nChoosek(int n, int k)
{
    if (n < k || k < 0) {
        printf("Wrong argument for combination. (%d, %d)", n, k);
        return 1;
    }

    if (k > n / 2) k = n - k;
    if (k == 1) return n;
    if (k == 0) return 1;

    int c = 1;
    for (int i = 1; i <= k; i++, n--) (c *= n) /= i;
    return c;
}

 
 
int ijk2Index(int i, int j, int k, int n) 
{
    // the whole tet - the top tet + current triangle
    return (n + 2) * (n + 1) * n / 6 - (n - k + 2) * (n - k + 1) * (n - k) / 6 +
        j * (n - k) - j * (j - 1) / 2 + i;
}

 