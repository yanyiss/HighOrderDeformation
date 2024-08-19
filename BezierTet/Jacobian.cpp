#include"Jacobian.h"
#include <iostream>
#include <fstream>
#include <iomanip>

 
 
bool _lessMinB::operator()(std::shared_ptr<_coeffData> cd1, std::shared_ptr<_coeffData> cd2) const
{
    return cd1->minB() > cd2->minB();
}

bool _lessMaxB::operator()(std::shared_ptr<_coeffData> cd1, std::shared_ptr <_coeffData> cd2) const
{
    return cd1->maxB() < cd2->maxB();
}

 
template <typename Comp>
void _subdivideDomainsMinOrMax(std::vector<std::shared_ptr<_coeffData>> domains, int& tag)
{
	//std::cout << "=========================  Start  ===================" << std::endl;
	std::vector<std::shared_ptr<_coeffData>> subs;
	make_heap(domains.begin(), domains.end(), Comp());
	int k = 0;
	const int max_subdivision = 100;

	while ( k < max_subdivision)
	{
		if (domains.empty()) break;
		std::shared_ptr<_coeffData> cd = domains[0];
		pop_heap(domains.begin(), domains.end(), Comp());
		domains.pop_back();
		cd->getSubCoeff(subs); 

		for (std::size_t i = 0; i < subs.size(); i++)
		{
			if (subs[i]->minL() < 0.) 
			{
				tag = -1;
				//std::cout << "=================  Flip   subdivision num is: "<< k  <<"  =====================" << std::endl;
				return;
			}



			if (subs[i]->minB() > 0.) 
			{
				//std::cout << "***************** " << subs[i]->minB() << std::endl;
				continue; 
			}
			else if (subs[i]->maxB() <= 0.) 
			{
				tag = -1;
				//std::cout << "=================  Flip   subdivision num is: " << k << "  =====================" << std::endl;
				return;
			}
			else//subs[i]->minB()<0 && subs[i]->maxB()>0
			{
				//std::cout << "################## " << subs[i]->minB() << std::endl;
				//add_num++;
				domains.push_back(subs[i]);
				push_heap(domains.begin(), domains.end(), Comp());
			}
		}
		//std::cout << "******************** remaining subs is: " << add_num << " **********************" << std::endl;
		++k;
	}


	 
	if (k != max_subdivision)
	{

		tag = 1;
		//std::cout << "============== det is positive , No Flip ===================" << std::endl;
		//std::cout << "============== Number of subdivisions: " << k <<"======================" << std::endl;
	}
	else 
	{
		tag = 0;
		std::cout << "================  error : arrive at Max subdivision  =========================== " << std::endl;

	}


}



// Miscellaneous
template <typename Comp>
void _subdivideDomainsMinOrMax(std::vector<std::shared_ptr<_coeffData>> domains,
	double& minL, double& maxL, bool debug)
{
	std::vector<std::shared_ptr<_coeffData>> subs;
	make_heap(domains.begin(), domains.end(), Comp());
	int k = 0;
	const int max_subdivision = 1000;
	while (!domains[0]->boundsOk(minL, maxL) && k + 1 < max_subdivision) {
		 
		std::shared_ptr<_coeffData> cd = domains[0];
		pop_heap(domains.begin(), domains.end(), Comp());
		domains.pop_back();
		cd->getSubCoeff(subs);
		/*cd->deleteBezierCoeff();
		delete cd;*/

		for (std::size_t i = 0; i < subs.size(); i++) {
			minL = std::min(minL, subs[i]->minL());
			maxL = std::max(maxL, subs[i]->maxL());
			domains.push_back(subs[i]);
			push_heap(domains.begin(), domains.end(), Comp());
		}
		++k;
		if (domains.empty()) break; 
	}
	if (debug) { std::cout << "Number of subdivisions: " << k << std::endl; }
	else if (k == max_subdivision) {
		std::printf("Max subdivision (%d) (size domains %d)", max_subdivision, domains.size());
	}
}

// Jacobian determinant (for validity of all elements)
_coeffDataJac::_coeffDataJac( std::shared_ptr<bezierCoeff> coeffs)
    : _coeffData(), _coeffs(coeffs)
{
    const bezierCoeff& coeff = (*_coeffs);

    _minL = _maxL = coeff.getCornerCoeff(0);
    for (int i = 1; i < 4; i++) { 
        _minL = std::min(_minL, coeff.getCornerCoeff(i));
        _maxL = std::max(_maxL, coeff.getCornerCoeff(i));
    }
    _minB = _maxB = coeff(0);
    for (int i = 1; i < coeff.getNumCoeff(); i++) {
        _minB = std::min(_minB, coeff(i));
        _maxB = std::max(_maxB, coeff(i));
    }
}


int bezierCoeff::getIdxCornerCoeff(int i) const
{
    const int order = _order; 
    switch (i) {
    case 0: return 0;
    case 1: return order;
    case 2: return (order + 2) * (order + 1) / 2 - 1;
    case 3: return _r - 1;
    }
}

void bezierCoeff::subdivide(std::vector<std::shared_ptr< bezierCoeff>>& subCoeff) const
{
    if (subCoeff.size()) {
        std::printf("expected empty vector of bezierCoeff");
        subCoeff.clear();
    }
	for (int i = 0; i < 8; ++i)
	{
		 
		std::shared_ptr<bezierCoeff> tmp_bc = std::make_shared<bezierCoeff>(*this);
		subCoeff.push_back(tmp_bc);
	}
    _subdivideTetrahedron(*this, subCoeff);
    return;
}


void bezierCoeff::_subdivideTetrahedron(const bezierCoeff& coeff,
    std::vector<std::shared_ptr< bezierCoeff>>& vSubCoeff)
{
	int order;
	if (coeff._r == 84)
	{
		order = 3;
	}
	else if (coeff._r == 20)
	{
		order = 2;
	}
	else
	{
		std::cout << "#################### Error : Noly support order 2 or 3" << std::endl;
	}

    const int n = 3*(order-1) + 1; 
    const int N = (n + 2) * (n + 1) * n / 6; 

    bezierCoeff& sub1 = *vSubCoeff[0];
    bezierCoeff& sub2 = *vSubCoeff[1];
    bezierCoeff& sub3 = *vSubCoeff[2];
    bezierCoeff& sub4 = *vSubCoeff[3];
    bezierCoeff& sub5 = *vSubCoeff[4];
    bezierCoeff& sub6 = *vSubCoeff[5];
    bezierCoeff& sub7 = *vSubCoeff[6];
    bezierCoeff& sub8 = *vSubCoeff[7];

    // Corner (0,0,0)
    _copy(coeff, 0, N, sub1);
    _subdivideTet(subdivU, n, sub1);
    _subdivideTet(subdivV, n, sub1);
    _subdivideTet(subdivW, n, sub1);

    // Compute 4 middle ones
    _copy(sub1, 0, N, sub2);
    _subdivideTet(node0CrossEdge12, n, sub2);

    _copy(sub2, 0, N, sub3);
    _copy(sub2, 0, N, sub4);
    _subdivideTet(node1CrossEdge03, n, sub3);
    _subdivideTet(node2CrossEdge03, n, sub4);

    _copy(sub4, 0, N, sub5);
    _subdivideTet(node1CrossEdge03, n, sub5);

    // 3 remaining corners
    _copy(sub3, 0, N, sub6);
    _copy(sub4, 0, N, sub7);
    _copy(sub5, 0, N, sub8);
    _subdivideTet(node3CrossEdge12, n, sub6);
    _subdivideTet(node3CrossEdge12, n, sub7);
    _subdivideTet(node0CrossEdge12, n, sub8);
    // node 3 cross edge 1-2
}

void bezierCoeff::_copy(const bezierCoeff& from, int start, int num,
    bezierCoeff& to)
{
    const int dim = from._c;
    for (int i = start; i < start + num; ++i) {
        for (int j = 0; j < dim; ++j) { to(i, j) = from(i, j); }
    }
}

 void bezierCoeff::_subdivideTet(SubdivisionTet which, int n,
    bezierCoeff& coeff)
{
    // TODO: consider precompute vector<pair<int, int>> for subdiv
  //       consider precompute vector<pair<int, int, int>> for n_crosse_e
    const int dim = coeff.getNumColumns(); 
    switch (which) {
    case subdivU:
        for (int iter = 1; iter < n; ++iter) {
            for (int k = 0; k < n - iter; ++k) {
                for (int j = 0; j < n - iter - k; ++j) {
                    for (int i = n - 1 - j - k; i >= iter; --i) {
                        const int I = _ijk2Index(i, j, k, n);
                        const int Im = _ijk2Index(i - 1, j, k, n);
                        for (int K = 0; K < dim; ++K) {
                            coeff(I, K) = .5 * (coeff(Im, K) + coeff(I, K));
                        }
                    }
                }
            }
        }
        return;
    case subdivV:
        for (int iter = 1; iter < n; ++iter) {
            for (int k = 0; k < n - iter; ++k) {
                for (int j = n - 1 - k; j >= iter; --j) {
                    for (int i = 0; i < n - j - k; ++i) {
                        const int I = _ijk2Index(i, j, k, n);
                        const int Im = _ijk2Index(i, j - 1, k, n);
                        for (int K = 0; K < dim; ++K) {
                            coeff(I, K) = .5 * (coeff(Im, K) + coeff(I, K));
                        }
                    }
                }
            }
        }
        return;
    case subdivW:
        for (int iter = 1; iter < n; ++iter) {
            for (int k = n - 1; k >= iter; --k) {
                for (int j = 0; j < n - k; ++j) {
                    for (int i = 0; i < n - j - k; ++i) {
                        const int I = _ijk2Index(i, j, k, n);
                        const int Im = _ijk2Index(i, j, k - 1, n);
                        for (int K = 0; K < dim; ++K) {
                            coeff(I, K) = .5 * (coeff(Im, K) + coeff(I, K));
                        }
                    }
                }
            }
        }
        return;
        // TODO: consider precompute vector<tuple<int, int, int>> for this
    case node0CrossEdge12:
        for (int iter = 1; iter < n; ++iter) {
            for (int k = 0; k < n - iter; ++k) {
                for (int j = 0; j < n - iter - k; ++j) {
                    for (int i = 0; i < n - iter - j - k; ++i) {
                        const int I = _ijk2Index(i, j, k, n);
                        const int Ia = _ijk2Index(i + 1, j, k, n);
                        const int Ib = _ijk2Index(i, j + 1, k, n);
                        for (int K = 0; K < dim; ++K) {
                            coeff(I, K) = coeff(Ia, K) + coeff(Ib, K) - coeff(I, K);
                        }
                    }
                }
            }
        }
        return;
    case node3CrossEdge12:
        for (int iter = 1; iter < n; ++iter) {
            for (int k = n - 1; k >= iter; --k) {
                for (int j = 0; j < n - k; ++j) {
                    for (int i = 0; i < n - j - k; ++i) {
                        const int I = _ijk2Index(i, j, k, n);
                        const int Ia = _ijk2Index(i + 1, j, k - 1, n);
                        const int Ib = _ijk2Index(i, j + 1, k - 1, n);
                        for (int K = 0; K < dim; ++K) {
                            coeff(I, K) = coeff(Ia, K) + coeff(Ib, K) - coeff(I, K);
                        }
                    }
                }
            }
        }
        return;
    case node1CrossEdge03:
        for (int iter = 1; iter < n; ++iter) {
            for (int k = 0; k < n - iter; ++k) {
                for (int j = 0; j < n - iter - k; ++j) {
                    for (int i = n - 1 - j - k; i >= iter; --i) {
                        const int I = _ijk2Index(i, j, k, n);
                        const int Ia = _ijk2Index(i - 1, j, k, n);
                        const int Ib = _ijk2Index(i - 1, j, k + 1, n);
                        for (int K = 0; K < dim; ++K) {
                            coeff(I, K) = coeff(Ia, K) + coeff(Ib, K) - coeff(I, K);
                        }
                    }
                }
            }
        }
        return;
    case node2CrossEdge03:
        for (int iter = 1; iter < n; ++iter) {
            for (int k = 0; k < n - iter; ++k) {
                for (int j = n - 1 - k; j >= iter; --j) {
                    for (int i = 0; i < n - j - k; ++i) {
                        const int I = _ijk2Index(i, j, k, n);
                        const int Ia = _ijk2Index(i, j - 1, k, n);
                        const int Ib = _ijk2Index(i, j - 1, k + 1, n);
                        for (int K = 0; K < dim; ++K) {
                            coeff(I, K) = coeff(Ia, K) + coeff(Ib, K) - coeff(I, K);
                        }
                    }
                }
            }
        }
    }








}

 
void _subdivideDomains(std::vector<std::shared_ptr<_coeffData>> domains,  int& tag) 
{
    if (domains.empty()) {
        std::cout << "Empty vector in Bezier subdivision, nothing to do" << std::endl;
        return;
    }
    double minL = domains[0]->minL();
    double maxL = domains[0]->maxL();
    for (std::size_t i = 1; i < domains.size(); ++i) {
		 
        minL = std::min(minL, domains[i]->minL());
        maxL = std::max(maxL, domains[i]->maxL());
    }
    

    if (minL < 0.) 
    {
        tag = -1;
        std::cout << "=================  Flip :  initail corner  =====================" << std::endl;
        return;

    }
	//std::cout << "===================== Now start check =============" << std::endl;
    _subdivideDomainsMinOrMax<_lessMinB>(domains, tag);




}

void _subdivideDomains(std::vector<std::shared_ptr<_coeffData>> domains, bool alsoMax,
    bool debug,int &tag)
{
    if (domains.empty()) {
        std::cout << "Empty vector in Bezier subdivision, nothing to do" << std::endl;
        return;
    }
    double minL = domains[0]->minL();
    double maxL = domains[0]->maxL();
    for (std::size_t i = 1; i < domains.size(); ++i) {
        minL = std::min(minL, domains[i]->minL());
        maxL = std::max(maxL, domains[i]->maxL());
    }

    _subdivideDomainsMinOrMax<_lessMinB>(domains, minL, maxL, debug);
    if (alsoMax)
        _subdivideDomainsMinOrMax<_lessMaxB>(domains, minL, maxL, debug);
}


 
bool _coeffDataJac::boundsOk(double minL, double maxL) const
{
    double tol = std::max(std::abs(minL), std::abs(maxL)) * 1e-3;
    return (minL <= 0 || _minB > 0) && (maxL >= 0 || _maxB < 0) &&
        minL - _minB < tol&& _maxB - maxL < tol;
    // NB: First condition implies minL and minB both positive or both negative
}
 void _coeffDataJac::getSubCoeff(std::vector<std::shared_ptr<_coeffData>> &v) const
{
    std::vector<std::shared_ptr<bezierCoeff>> sub;
    _coeffs->subdivide(sub);


 
	v.clear();

    for (std::size_t i = 0; i < sub.size(); i++) {
		std::shared_ptr<_coeffDataJac> tmp_cd = std::make_shared<_coeffDataJac>(sub[i]);
        v.push_back(tmp_cd);
    }
}



 

bezierCoeff::bezierCoeff(const bezierCoeff& other,bool swap)
{
	_r = other._r;
	_c = other._c;
	_order = other._order;
	if (swap)
	{

		_data = other._data;
	}
	else
	{
		_data = new double[_r * _c];
		for (int i = 0; i < _r; i++) _data[i] = other._data[i];
	}
};

double fac(int n)
{
	if (n == 0)
		return 1.0;
	if (n == 1)
		return 1.0;
	if (n == 2)
		return 2.0;
	if (n == 3)
		return 6.0;
	if (n == 4)
		return 24.0;
	if (n == 5)
		return 120.0;
	return n * fac(n - 1);
}




fullMatrix<double> generateBez2LagMatrix(const fullMatrix<double>& exponent,
	const fullMatrix<double>& point,
	int order, int dimSimplex)
{

	if (exponent.size1() != point.size1() || exponent.size2() != point.size2()) {
		printf("Wrong sizes for bez2lag matrix generation %d %d -- %d %d",
			exponent.size1(), point.size1(), exponent.size2(),
			point.size2());
		return fullMatrix<double>(1, 1);
	}

	int ndofs = exponent.size1();
	int dim = exponent.size2();

	fullMatrix<double> bez2Lag(ndofs, ndofs);
	for (int i = 0; i < ndofs; i++) {
		for (int j = 0; j < ndofs; j++) {
			double dd = 1.;
			{
				double pointCompl = 1.;
				int exponentCompl = order;
				for (int k = 0; k < dimSimplex; k++) {
					dd *= nChoosek(exponentCompl, (int)exponent(i, k)) *
						pow(point(j, k), exponent(i, k));
					pointCompl -= point(j, k);
					exponentCompl -= (int)exponent(i, k);
				}
				dd *= pow(pointCompl, exponentCompl);
			}

			for (int k = dimSimplex; k < dim; k++)
				dd *= nChoosek(order, (int)exponent(i, k)) *
				pow(point(j, k), exponent(i, k)) *
				pow(1. - point(j, k), order - exponent(i, k));

			bez2Lag(j, i) = dd;
		}
	}
	return bez2Lag;












}


void gmshGenerateOrderedPoints( int order,fullMatrix<double>& points,bool onBezierDomain) 
{
	gmshGenerateOrderedMonomials(order, points);
	if (points.size1() == 1) return;
	if (onBezierDomain)
	{
		points.scale(1. / order);
		return;
	}


}


