#pragma once
#include <set>
#include <map>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "fullMatrix.h"


 

 

class bezierBasis
{
private:

    int _dimSimplex;
    int _order; 
    fullMatrix<double> _exponents;
  
    
    friend class bezierBasisRaiser;
    friend class bezierCoeff;


public:
    // Constructors
    bezierBasis(int order);
    ~bezierBasis() {};

    // get methods
    inline int getDim() const { return _exponents.size2(); }
    inline int getDimSimplex() const { return _dimSimplex; }
    inline int getNumCoeff() const { return _exponents.size1(); }
    inline int getOrder() const { return _order; }
     
    const bezierBasisRaiser* getRaiser() const;
    
   /* inline const fullMatrix<double>& getSamplingPointsToComputeBezierCoeff() const
    {
        return _samplingPntsLagDomain;
    }*/

private:
    void _construct();
    


};

class bezierBasisRaiser
{
    // Let f, g, h be three function whose Bezier coefficients are given.
  // This class allows to compute the Bezier coefficients of f*g and f*g*h.
private:
    class _data {
        friend class bezierBasisRaiser;

    private:
        int i, j, k;
        double val;

    public:
        _data(double vv, int ii, int jj = -1, int kk = -1)
            : i(ii), j(jj), k(kk), val(vv)
        {
        }
    };
    std::vector<std::vector<_data> > _raiser2; 
    std::vector<std::vector<_data> > _raiser3; 
    const bezierBasis* _bfs;

public:
    bezierBasisRaiser(const bezierBasis* bezier) : _bfs(bezier)
    {
        _fillRaiserData();
    };
    void computeCoeff( fullVector<double>& coeffA,
         fullVector<double>& coeffB,
        fullVector<double>& coeffSquare) ;

     

    void computeCoeff(fullVector<double>& coeffA,
        fullVector<double>& coeffB,
        fullVector<double>& coeffC,
        fullVector<double>& coeffCubic) ;
     
private:
    void _fillRaiserData();
};


void double2int(const fullMatrix<double>& matDouble, fullMatrix<int>& matInt);

void generateExponents(int order, fullMatrix<double>& exp);

int nChoosek(int n, int k);

void gmshGenerateOrderedMonomials(int order, fullMatrix<double>& monomials);

 

int ijk2Index(int i, int j, int k, int n);
