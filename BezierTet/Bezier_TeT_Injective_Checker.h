#pragma once
#include"Jacobian.h"
#include <iostream>
#include <fstream>


//The order of Bezier control points: that is the order in Gmsh.
/* tet order 3 FIXME: check the plot
 *
 *              2
 *            ,/|`\
 *          ,8  |  `7              E = order - 1
 *        ,/    13   `\            C = 4 + 6*E
 *      ,9       |     `6          F = ((order - 1)*(order - 2))/2
 *    ,/         |       `\        N = total number of vertices
 *   0-----4-----'.--5-----1
 *    `\.         |      ,/        Interior vertex numbers
 *       11.     12    ,15           for edge 0 <= i <= 5: 4+i*E to 4+(i+1)*E-1
 *          `\.   '. 14              for face 0 <= j <= 3: C+j*F to C+(j+1)*F-1
 *             10\.|/        in volume           : C+4*F to N-1
 *                `3
 *
 */


//支持2次或者3次的Bezier四面体的翻转检查
class Bezier_TeT_Injective_Checker
{

public:
	Bezier_TeT_Injective_Checker();
	~Bezier_TeT_Injective_Checker();
	Bezier_TeT_Injective_Checker(int input_tet_order);

public:
	//Judgment of flipping of cubic Bezier tetrahedron
	int Tet_Order3_is_definitely_injective_by_determinant(std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z);

	int Tet_Order3_is_definitely_injective_by_determinant_By_Cal_Extreme(std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z);

   //***********************************

	//Flip judgment of quadratic Bezier tetrahedron
	int Tet_Order2_is_definitely_injective_by_determinant(std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z);

	int Tet_Order2_is_definitely_injective_by_determinant_By_Cal_Extreme(std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z);

private:
	int tet_order;//The degree of the input tetrahedron
	int derivative_order;//the number of derivatives after 1, that is tet_order-1
	bezierBasis* bezier;
	bezierBasisRaiser* raiser;
};


