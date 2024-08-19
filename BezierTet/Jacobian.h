#pragma once
#include <vector>
#include"bezierBasis.h"
#include <Eigen/Dense>



class bezierCoeff
{ 
private:
    
    int _order; 
    int _r, _c;  
    double* _data; 



public:
    bezierCoeff() {};
   
    bezierCoeff(const bezierCoeff& other, bool swap = false);
    bezierCoeff(fullVector<double>& coeffCubic,int order)
    {
        _r = coeffCubic.size();
        _c = 1;

        _data = new double[_r * _c];
        for (int i = 0; i < _r; i++) _data[i] = coeffCubic(i);
        //_data = coeffCubic.getDataPtr();
        _order = order;
    };
    ~bezierCoeff()
    {
        delete[] _data;
    };



    int getIdxCornerCoeff(int i) const;
    inline int getNumCoeff() const { return _r; }
    inline int getNumColumns() const { return _c; }
    inline double getCornerCoeff(int k) const
    {
        return _data[getIdxCornerCoeff(k)]; 
    }

    inline double getCornerCoeff(int k, int j) const
    {
        return _data[getIdxCornerCoeff(k) + _r * j];
    }
    inline double operator()(int i) const { return _data[i]; }
    inline double operator()(int i, int j) const { return _data[i + _r * j]; } 
    inline double& operator()(int i) { return _data[i]; }
    inline double& operator()(int i, int j) { return _data[i + _r * j]; }

    void subdivide(std::vector<std::shared_ptr<bezierCoeff>>& subCoeff) const;

private:
    enum SubdivisionTet {
        subdivU,
        subdivV,
        subdivW,
        node0CrossEdge12,
        node3CrossEdge12,
        node1CrossEdge03,
        node2CrossEdge03
    };
    static void _subdivideTet(SubdivisionTet which, int n, bezierCoeff& coeff);

    inline static int _ij2Index(int i, int j, int n)
    {
        return i + j * n - j * (j - 1) / 2;
    }
    inline static int _ijk2Index(int i, int j, int k, int n) 
    {
        // the whole tet - the top tet + current triangle
        return (n + 2) * (n + 1) * n / 6 - (n - k + 2) * (n - k + 1) * (n - k) / 6 +
            j * (n - k) - j * (j - 1) / 2 + i;
    }
    static void _subdivideTetrahedron(const bezierCoeff& coeff,
        std::vector<std::shared_ptr< bezierCoeff>>& vSubCoeff);
    static void _copy(const bezierCoeff& from, int start, int num,
        bezierCoeff& to);

};


class _coeffData {
protected: 
    double _minL, _maxL; // Extremum of measure at corners  
    double _minB, _maxB; // Extremum of measure  
public:
    _coeffData() : _minL(0), _maxL(0), _minB(0), _maxB(0) {}
    virtual ~_coeffData() {}

    inline double minL() const { return _minL; }
    inline double maxL() const { return _maxL; }
    inline double minB() const { return _minB; }
    inline double maxB() const { return _maxB; }

    virtual bool boundsOk(double minL, double maxL) const = 0;
    //virtual void getSubCoeff(std::vector<std::shared_ptr<_coeffData>>  ) const = 0;
    virtual void getSubCoeff(std::vector<std::shared_ptr<_coeffData>>& v) const = 0;

    //virtual void deleteBezierCoeff() = 0;
    //virtual  const bezierCoeff* Get_mycoeffs() =0;
};

struct _lessMinB {
    bool operator()(std::shared_ptr<_coeffData>,std::shared_ptr<_coeffData>) const;
};
struct _lessMaxB {
    bool operator()(std::shared_ptr< _coeffData>,std::shared_ptr<_coeffData>) const;
};


class _coeffDataJac : public _coeffData {
private:
    const std::shared_ptr<bezierCoeff> _coeffs;

public:
    _coeffDataJac(const std::shared_ptr<bezierCoeff> coeffs);
    ~_coeffDataJac() {}

public:
    bool boundsOk(double minL, double maxL) const;
    //void getSubCoeff(std::vector<std::shared_ptr<_coeffData>>  ) const;
    void getSubCoeff(std::vector<std::shared_ptr<_coeffData>> &v) const;

    //void deleteBezierCoeff() {};
    /*const bezierCoeff* Get_mycoeffs()
    {
        return _coeffs;
    }*/
};

 

void _subdivideDomains(std::vector<std::shared_ptr<_coeffData>> domains, bool alsoMax,
    bool debug, int& tag); 

void _subdivideDomains(std::vector<std::shared_ptr<_coeffData>> domains, int& tag);

 
double fac(int n);
 
 fullMatrix<double> generateBez2LagMatrix(const fullMatrix<double>& exponent,
    const fullMatrix<double>& point,
    int order, int dimSimplex);


 


void gmshGenerateOrderedPoints(int order, fullMatrix<double>& points, bool onBezierDomain);