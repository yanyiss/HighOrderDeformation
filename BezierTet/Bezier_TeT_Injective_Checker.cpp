#include "Bezier_TeT_Injective_Checker.h"
#include <iomanip>

 

Bezier_TeT_Injective_Checker::Bezier_TeT_Injective_Checker(int input_tet_order)
{
	tet_order = input_tet_order;
	derivative_order = tet_order - 1;

	if (bezier != nullptr)
	{
		bezier = nullptr;
	}

	bezier = new bezierBasis(derivative_order);

	if (raiser != nullptr) {
		raiser = nullptr;
	}

	raiser = new bezierBasisRaiser(bezier);

}

Bezier_TeT_Injective_Checker::~Bezier_TeT_Injective_Checker()
{
	if (raiser != nullptr) {
		delete raiser;
	}

	if (bezier != nullptr) {
		delete bezier;
	}
}

int Bezier_TeT_Injective_Checker::Tet_Order3_is_definitely_injective_by_determinant_By_Cal_Extreme(std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z)
{
	if (tet_order != 3)
	{
		std::cout << "============== Error: arrive at Max subdivision num ================" << std::endl;
		return 0; 
	}
	
	int order = derivative_order;
	fullVector<double>  coeffA(10);
	fullVector<double> coeffB(10);
	fullVector<double> coeffC(10);
	fullVector<double> coeffCubic;
	fullVector<double> temp_coeffCubic;
	coeffCubic.resize((3 * order + 1) * (3 * order + 2) * (3 * order + 3) / 6, true); 

	 

	//(-uz)*vy*wx
		//(-uz)
	coeffA(0) = -3. * (_x[11] - _x[0]);
	coeffA(2) = -3. * (_x[15] - _x[5]);
	coeffA(5) = -3. * (_x[13] - _x[8]);
	coeffA(9) = -3. * (_x[3] - _x[10]);
	coeffA(1) = -3. * (_x[17] - _x[4]);
	coeffA(4) = -3. * (_x[19] - _x[16]);//
	coeffA(3) = -3. * (_x[18] - _x[9]);
	coeffA(6) = -3. * (_x[10] - _x[11]);
	coeffA(8) = -3. * (_x[12] - _x[18]);
	coeffA(7) = -3. * (_x[14] - _x[17]);

	//vy
	coeffB(0) = 3. * (_y[9] - _y[0]);
	coeffB(2) = 3. * (_y[6] - _y[5]);
	coeffB(5) = 3. * (_y[2] - _y[8]);
	coeffB(9) = 3. * (_y[12] - _y[10]);
	coeffB(1) = 3. * (_y[16] - _y[4]);//
	coeffB(4) = 3. * (_y[7] - _y[16]);//
	coeffB(3) = 3. * (_y[8] - _y[9]);
	coeffB(6) = 3. * (_y[18] - _y[11]);
	coeffB(8) = 3. * (_y[13] - _y[18]);
	coeffB(7) = 3. * (_y[19] - _y[17]);//

	//wx
	coeffC(0) = 3. * (_z[4] - _z[0]);
	coeffC(2) = 3. * (_z[1] - _z[5]);
	coeffC(5) = 3. * (_z[7] - _z[8]);
	coeffC(9) = 3. * (_z[14] - _z[10]);
	coeffC(1) = 3. * (_z[5] - _z[4]);
	coeffC(4) = 3. * (_z[6] - _z[16]);//
	coeffC(3) = 3. * (_z[16] - _z[9]);//
	coeffC(6) = 3. * (_z[17] - _z[11]);
	coeffC(8) = 3. * (_z[19] - _z[18]);//
	coeffC(7) = 3. * (_z[15] - _z[17]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uy* vz *wx
	//uy
	coeffA(0) = 3. * (_x[9] - _x[0]);
	coeffA(2) = 3. * (_x[6] - _x[5]);
	coeffA(5) = 3. * (_x[2] - _x[8]);
	coeffA(9) = 3. * (_x[12] - _x[10]);
	coeffA(1) = 3. * (_x[16] - _x[4]);//
	coeffA(4) = 3. * (_x[7] - _x[16]);//
	coeffA(3) = 3. * (_x[8] - _x[9]);
	coeffA(6) = 3. * (_x[18] - _x[11]);
	coeffA(8) = 3. * (_x[13] - _x[18]);
	coeffA(7) = 3. * (_x[19] - _x[17]);//
	//vz
	coeffB(0) = 3. * (_y[11] - _y[0]);
	coeffB(2) = 3. * (_y[15] - _y[5]);
	coeffB(5) = 3. * (_y[13] - _y[8]);
	coeffB(9) = 3. * (_y[3] - _y[10]);
	coeffB(1) = 3. * (_y[17] - _y[4]);
	coeffB(4) = 3. * (_y[19] - _y[16]);//
	coeffB(3) = 3. * (_y[18] - _y[9]);
	coeffB(6) = 3. * (_y[10] - _y[11]);
	coeffB(8) = 3. * (_y[12] - _y[18]);
	coeffB(7) = 3. * (_y[14] - _y[17]);
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uz* vx* wy
	//uz
	coeffA(0) = 3. * (_x[11] - _x[0]);
	coeffA(2) = 3. * (_x[15] - _x[5]);
	coeffA(5) = 3. * (_x[13] - _x[8]);
	coeffA(9) = 3. * (_x[3] - _x[10]);
	coeffA(1) = 3. * (_x[17] - _x[4]);
	coeffA(4) = 3. * (_x[19] - _x[16]);//
	coeffA(3) = 3. * (_x[18] - _x[9]);
	coeffA(6) = 3. * (_x[10] - _x[11]);
	coeffA(8) = 3. * (_x[12] - _x[18]);
	coeffA(7) = 3. * (_x[14] - _x[17]);
	//vx
	coeffB(0) = 3. * (_y[4] - _y[0]);
	coeffB(2) = 3. * (_y[1] - _y[5]);
	coeffB(5) = 3. * (_y[7] - _y[8]);
	coeffB(9) = 3. * (_y[14] - _y[10]);
	coeffB(1) = 3. * (_y[5] - _y[4]);
	coeffB(4) = 3. * (_y[6] - _y[16]);//
	coeffB(3) = 3. * (_y[16] - _y[9]);//
	coeffB(6) = 3. * (_y[17] - _y[11]);
	coeffB(8) = 3. * (_y[19] - _y[18]);//
	coeffB(7) = 3. * (_y[15] - _y[17]);
	//wy
	coeffC(0) = 3. * (_z[9] - _z[0]);
	coeffC(2) = 3. * (_z[6] - _z[5]);
	coeffC(5) = 3. * (_z[2] - _z[8]);
	coeffC(9) = 3. * (_z[12] - _z[10]);
	coeffC(1) = 3. * (_z[16] - _z[4]);//
	coeffC(4) = 3. * (_z[7] - _z[16]);//
	coeffC(3) = 3. * (_z[8] - _z[9]);
	coeffC(6) = 3. * (_z[18] - _z[11]);
	coeffC(8) = 3. * (_z[13] - _z[18]);
	coeffC(7) = 3. * (_z[19] - _z[17]);//
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-ux) * vz * wy
	//-ux
	coeffA(0) = -3. * (_x[4] - _x[0]);
	coeffA(2) = -3. * (_x[1] - _x[5]);
	coeffA(5) = -3. * (_x[7] - _x[8]);
	coeffA(9) = -3. * (_x[14] - _x[10]);
	coeffA(1) = -3. * (_x[5] - _x[4]);
	coeffA(4) = -3. * (_x[6] - _x[16]);//
	coeffA(3) = -3. * (_x[16] - _x[9]);//
	coeffA(6) = -3. * (_x[17] - _x[11]);
	coeffA(8) = -3. * (_x[19] - _x[18]);//
	coeffA(7) = -3. * (_x[15] - _x[17]);
	//vz
	coeffB(0) = 3. * (_y[11] - _y[0]);
	coeffB(2) = 3. * (_y[15] - _y[5]);
	coeffB(5) = 3. * (_y[13] - _y[8]);
	coeffB(9) = 3. * (_y[3] - _y[10]);
	coeffB(1) = 3. * (_y[17] - _y[4]);
	coeffB(4) = 3. * (_y[19] - _y[16]);//
	coeffB(3) = 3. * (_y[18] - _y[9]);
	coeffB(6) = 3. * (_y[10] - _y[11]);
	coeffB(8) = 3. * (_y[12] - _y[18]);
	coeffB(7) = 3. * (_y[14] - _y[17]);
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-uy) *vx *wz
	//-uy
	coeffA(0) = -3. * (_x[9] - _x[0]);
	coeffA(2) = -3. * (_x[6] - _x[5]);
	coeffA(5) = -3. * (_x[2] - _x[8]);
	coeffA(9) = -3. * (_x[12] - _x[10]);
	coeffA(1) = -3. * (_x[16] - _x[4]);//
	coeffA(4) = -3. * (_x[7] - _x[16]);//
	coeffA(3) = -3. * (_x[8] - _x[9]);
	coeffA(6) = -3. * (_x[18] - _x[11]);
	coeffA(8) = -3. * (_x[13] - _x[18]);
	coeffA(7) = -3. * (_x[19] - _x[17]);//
	//vx
	coeffB(0) = 3. * (_y[4] - _y[0]);
	coeffB(2) = 3. * (_y[1] - _y[5]);
	coeffB(5) = 3. * (_y[7] - _y[8]);
	coeffB(9) = 3. * (_y[14] - _y[10]);
	coeffB(1) = 3. * (_y[5] - _y[4]);
	coeffB(4) = 3. * (_y[6] - _y[16]);//
	coeffB(3) = 3. * (_y[16] - _y[9]);//
	coeffB(6) = 3. * (_y[17] - _y[11]);
	coeffB(8) = 3. * (_y[19] - _y[18]);//
	coeffB(7) = 3. * (_y[15] - _y[17]);
	//wz
	coeffC(0) = 3. * (_z[11] - _z[0]);
	coeffC(2) = 3. * (_z[15] - _z[5]);
	coeffC(5) = 3. * (_z[13] - _z[8]);
	coeffC(9) = 3. * (_z[3] - _z[10]);
	coeffC(1) = 3. * (_z[17] - _z[4]);
	coeffC(4) = 3. * (_z[19] - _z[16]);//
	coeffC(3) = 3. * (_z[18] - _z[9]);
	coeffC(6) = 3. * (_z[10] - _z[11]);
	coeffC(8) = 3. * (_z[12] - _z[18]);
	coeffC(7) = 3. * (_z[14] - _z[17]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//ux *vy* wz
	//ux
	coeffA(0) = 3. * (_x[4] - _x[0]);
	coeffA(2) = 3. * (_x[1] - _x[5]);
	coeffA(5) = 3. * (_x[7] - _x[8]);
	coeffA(9) = 3. * (_x[14] - _x[10]);
	coeffA(1) = 3. * (_x[5] - _x[4]);
	coeffA(4) = 3. * (_x[6] - _x[16]);//
	coeffA(3) = 3. * (_x[16] - _x[9]);//
	coeffA(6) = 3. * (_x[17] - _x[11]);
	coeffA(8) = 3. * (_x[19] - _x[18]);//
	coeffA(7) = 3. * (_x[15] - _x[17]);
	//vy
	coeffB(0) = 3. * (_y[9] - _y[0]);
	coeffB(2) = 3. * (_y[6] - _y[5]);
	coeffB(5) = 3. * (_y[2] - _y[8]);
	coeffB(9) = 3. * (_y[12] - _y[10]);
	coeffB(1) = 3. * (_y[16] - _y[4]);//
	coeffB(4) = 3. * (_y[7] - _y[16]);//
	coeffB(3) = 3. * (_y[8] - _y[9]);
	coeffB(6) = 3. * (_y[18] - _y[11]);
	coeffB(8) = 3. * (_y[13] - _y[18]);
	coeffB(7) = 3. * (_y[19] - _y[17]);//
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);



	//std::cout << "============================= Finished calulate coeffCubic ==================" << std::endl;


	 
	std::shared_ptr<bezierCoeff> bez = std::make_shared<bezierCoeff>(coeffCubic, 3 * order);


	// Refine coefficients
	std::shared_ptr<_coeffDataJac> tmp_cd = std::make_shared<_coeffDataJac>(bez);
	std::vector<std::shared_ptr< _coeffData>> domains(1, tmp_cd);
	int tag = -100;

	_subdivideDomains(domains, true, false, tag); 



	 
	 
	double min = std::numeric_limits<double>::max();
	double max = -min;
	for (std::size_t i = 0; i < domains.size(); ++i) {
		min = std::min(min, domains[i]->minB());
		max = std::max(max, domains[i]->maxB());
		 
	}

	std::cout << "======================= min: " << min << "  " << "max: " << max << " =======================" << std::endl;

	if (min > 0.) tag = 1;
	else if (max > 0.) tag = -1;
	else tag = 0;

	 
	if (tag == -1)
	{
		std::cout << "==============  Bezier TET appaer Flipped ================" << std::endl;
		return -1;
	}
	else if (tag == 1)
	{
		std::cout << "============== Bezier TET No Flip ================" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "============== Error: arrive at Max subdivision num ================" << std::endl;
		return 0;
	}






}



int Bezier_TeT_Injective_Checker::Tet_Order3_is_definitely_injective_by_determinant(std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z)

{
	if (tet_order != 3)
	{
		std::cout << "============== Error: input Bezier Tet Order is not 3 ================" << std::endl;
		return 0; 
	}

	int order = derivative_order;
	fullVector<double>  coeffA(10);
	fullVector<double> coeffB(10);
	fullVector<double> coeffC(10);
	fullVector<double> coeffCubic;
	fullVector<double> temp_coeffCubic;
	coeffCubic.resize((3 * order + 1) * (3 * order + 2) * (3 * order + 3) / 6, true); 

	//std::cout << "============================= Start calulate coeffCubic ==================" << std::endl;

	//(-uz)*vy*wx
		//(-uz)
	coeffA(0) = -3. * (_x[11] - _x[0]);
	coeffA(2) = -3. * (_x[15] - _x[5]);
	coeffA(5) = -3. * (_x[13] - _x[8]);
	coeffA(9) = -3. * (_x[3] - _x[10]);
	coeffA(1) = -3. * (_x[17] - _x[4]);
	coeffA(4) = -3. * (_x[19] - _x[16]);//
	coeffA(3) = -3. * (_x[18] - _x[9]);
	coeffA(6) = -3. * (_x[10] - _x[11]);
	coeffA(8) = -3. * (_x[12] - _x[18]);
	coeffA(7) = -3. * (_x[14] - _x[17]);

	//vy
	coeffB(0) = 3. * (_y[9] - _y[0]);
	coeffB(2) = 3. * (_y[6] - _y[5]);
	coeffB(5) = 3. * (_y[2] - _y[8]);
	coeffB(9) = 3. * (_y[12] - _y[10]);
	coeffB(1) = 3. * (_y[16] - _y[4]);//
	coeffB(4) = 3. * (_y[7] - _y[16]);//
	coeffB(3) = 3. * (_y[8] - _y[9]);
	coeffB(6) = 3. * (_y[18] - _y[11]);
	coeffB(8) = 3. * (_y[13] - _y[18]);
	coeffB(7) = 3. * (_y[19] - _y[17]);//

	//wx
	coeffC(0) = 3. * (_z[4] - _z[0]);
	coeffC(2) = 3. * (_z[1] - _z[5]);
	coeffC(5) = 3. * (_z[7] - _z[8]);
	coeffC(9) = 3. * (_z[14] - _z[10]);
	coeffC(1) = 3. * (_z[5] - _z[4]);
	coeffC(4) = 3. * (_z[6] - _z[16]);//
	coeffC(3) = 3. * (_z[16] - _z[9]);//
	coeffC(6) = 3. * (_z[17] - _z[11]);
	coeffC(8) = 3. * (_z[19] - _z[18]);//
	coeffC(7) = 3. * (_z[15] - _z[17]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uy* vz *wx
	//uy
	coeffA(0) = 3. * (_x[9] - _x[0]);
	coeffA(2) = 3. * (_x[6] - _x[5]);
	coeffA(5) = 3. * (_x[2] - _x[8]);
	coeffA(9) = 3. * (_x[12] - _x[10]);
	coeffA(1) = 3. * (_x[16] - _x[4]);//
	coeffA(4) = 3. * (_x[7] - _x[16]);//
	coeffA(3) = 3. * (_x[8] - _x[9]);
	coeffA(6) = 3. * (_x[18] - _x[11]);
	coeffA(8) = 3. * (_x[13] - _x[18]);
	coeffA(7) = 3. * (_x[19] - _x[17]);//
	//vz
	coeffB(0) = 3. * (_y[11] - _y[0]);
	coeffB(2) = 3. * (_y[15] - _y[5]);
	coeffB(5) = 3. * (_y[13] - _y[8]);
	coeffB(9) = 3. * (_y[3] - _y[10]);
	coeffB(1) = 3. * (_y[17] - _y[4]);
	coeffB(4) = 3. * (_y[19] - _y[16]);//
	coeffB(3) = 3. * (_y[18] - _y[9]);
	coeffB(6) = 3. * (_y[10] - _y[11]);
	coeffB(8) = 3. * (_y[12] - _y[18]);
	coeffB(7) = 3. * (_y[14] - _y[17]);
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uz* vx* wy
	//uz
	coeffA(0) = 3. * (_x[11] - _x[0]);
	coeffA(2) = 3. * (_x[15] - _x[5]);
	coeffA(5) = 3. * (_x[13] - _x[8]);
	coeffA(9) = 3. * (_x[3] - _x[10]);
	coeffA(1) = 3. * (_x[17] - _x[4]);
	coeffA(4) = 3. * (_x[19] - _x[16]);//
	coeffA(3) = 3. * (_x[18] - _x[9]);
	coeffA(6) = 3. * (_x[10] - _x[11]);
	coeffA(8) = 3. * (_x[12] - _x[18]);
	coeffA(7) = 3. * (_x[14] - _x[17]);
	//vx
	coeffB(0) = 3. * (_y[4] - _y[0]);
	coeffB(2) = 3. * (_y[1] - _y[5]);
	coeffB(5) = 3. * (_y[7] - _y[8]);
	coeffB(9) = 3. * (_y[14] - _y[10]);
	coeffB(1) = 3. * (_y[5] - _y[4]);
	coeffB(4) = 3. * (_y[6] - _y[16]);//
	coeffB(3) = 3. * (_y[16] - _y[9]);//
	coeffB(6) = 3. * (_y[17] - _y[11]);
	coeffB(8) = 3. * (_y[19] - _y[18]);//
	coeffB(7) = 3. * (_y[15] - _y[17]);
	//wy
	coeffC(0) = 3. * (_z[9] - _z[0]);
	coeffC(2) = 3. * (_z[6] - _z[5]);
	coeffC(5) = 3. * (_z[2] - _z[8]);
	coeffC(9) = 3. * (_z[12] - _z[10]);
	coeffC(1) = 3. * (_z[16] - _z[4]);//
	coeffC(4) = 3. * (_z[7] - _z[16]);//
	coeffC(3) = 3. * (_z[8] - _z[9]);
	coeffC(6) = 3. * (_z[18] - _z[11]);
	coeffC(8) = 3. * (_z[13] - _z[18]);
	coeffC(7) = 3. * (_z[19] - _z[17]);//
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-ux) * vz * wy
	//-ux
	coeffA(0) = -3. * (_x[4] - _x[0]);
	coeffA(2) = -3. * (_x[1] - _x[5]);
	coeffA(5) = -3. * (_x[7] - _x[8]);
	coeffA(9) = -3. * (_x[14] - _x[10]);
	coeffA(1) = -3. * (_x[5] - _x[4]);
	coeffA(4) = -3. * (_x[6] - _x[16]);//
	coeffA(3) = -3. * (_x[16] - _x[9]);//
	coeffA(6) = -3. * (_x[17] - _x[11]);
	coeffA(8) = -3. * (_x[19] - _x[18]);//
	coeffA(7) = -3. * (_x[15] - _x[17]);
	//vz
	coeffB(0) = 3. * (_y[11] - _y[0]);
	coeffB(2) = 3. * (_y[15] - _y[5]);
	coeffB(5) = 3. * (_y[13] - _y[8]);
	coeffB(9) = 3. * (_y[3] - _y[10]);
	coeffB(1) = 3. * (_y[17] - _y[4]);
	coeffB(4) = 3. * (_y[19] - _y[16]);//
	coeffB(3) = 3. * (_y[18] - _y[9]);
	coeffB(6) = 3. * (_y[10] - _y[11]);
	coeffB(8) = 3. * (_y[12] - _y[18]);
	coeffB(7) = 3. * (_y[14] - _y[17]);
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-uy) *vx *wz
	//-uy
	coeffA(0) = -3. * (_x[9] - _x[0]);
	coeffA(2) = -3. * (_x[6] - _x[5]);
	coeffA(5) = -3. * (_x[2] - _x[8]);
	coeffA(9) = -3. * (_x[12] - _x[10]);
	coeffA(1) = -3. * (_x[16] - _x[4]);//
	coeffA(4) = -3. * (_x[7] - _x[16]);//
	coeffA(3) = -3. * (_x[8] - _x[9]);
	coeffA(6) = -3. * (_x[18] - _x[11]);
	coeffA(8) = -3. * (_x[13] - _x[18]);
	coeffA(7) = -3. * (_x[19] - _x[17]);//
	//vx
	coeffB(0) = 3. * (_y[4] - _y[0]);
	coeffB(2) = 3. * (_y[1] - _y[5]);
	coeffB(5) = 3. * (_y[7] - _y[8]);
	coeffB(9) = 3. * (_y[14] - _y[10]);
	coeffB(1) = 3. * (_y[5] - _y[4]);
	coeffB(4) = 3. * (_y[6] - _y[16]);//
	coeffB(3) = 3. * (_y[16] - _y[9]);//
	coeffB(6) = 3. * (_y[17] - _y[11]);
	coeffB(8) = 3. * (_y[19] - _y[18]);//
	coeffB(7) = 3. * (_y[15] - _y[17]);
	//wz
	coeffC(0) = 3. * (_z[11] - _z[0]);
	coeffC(2) = 3. * (_z[15] - _z[5]);
	coeffC(5) = 3. * (_z[13] - _z[8]);
	coeffC(9) = 3. * (_z[3] - _z[10]);
	coeffC(1) = 3. * (_z[17] - _z[4]);
	coeffC(4) = 3. * (_z[19] - _z[16]);//
	coeffC(3) = 3. * (_z[18] - _z[9]);
	coeffC(6) = 3. * (_z[10] - _z[11]);
	coeffC(8) = 3. * (_z[12] - _z[18]);
	coeffC(7) = 3. * (_z[14] - _z[17]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//ux *vy* wz
	//ux
	coeffA(0) = 3. * (_x[4] - _x[0]);
	coeffA(2) = 3. * (_x[1] - _x[5]);
	coeffA(5) = 3. * (_x[7] - _x[8]);
	coeffA(9) = 3. * (_x[14] - _x[10]);
	coeffA(1) = 3. * (_x[5] - _x[4]);
	coeffA(4) = 3. * (_x[6] - _x[16]);//
	coeffA(3) = 3. * (_x[16] - _x[9]);//
	coeffA(6) = 3. * (_x[17] - _x[11]);
	coeffA(8) = 3. * (_x[19] - _x[18]);//
	coeffA(7) = 3. * (_x[15] - _x[17]);
	//vy
	coeffB(0) = 3. * (_y[9] - _y[0]);
	coeffB(2) = 3. * (_y[6] - _y[5]);
	coeffB(5) = 3. * (_y[2] - _y[8]);
	coeffB(9) = 3. * (_y[12] - _y[10]);
	coeffB(1) = 3. * (_y[16] - _y[4]);//
	coeffB(4) = 3. * (_y[7] - _y[16]);//
	coeffB(3) = 3. * (_y[8] - _y[9]);
	coeffB(6) = 3. * (_y[18] - _y[11]);
	coeffB(8) = 3. * (_y[13] - _y[18]);
	coeffB(7) = 3. * (_y[19] - _y[17]);//
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);



	//std::cout << "============================= Finished calulate coeffCubic ==================" << std::endl;


	 
	std::shared_ptr<bezierCoeff> bez = std::make_shared<bezierCoeff>(coeffCubic, 3 * order);


	// Refine coefficients
	std::shared_ptr<_coeffDataJac> tmp_cd = std::make_shared<_coeffDataJac>(bez);
	std::vector<std::shared_ptr< _coeffData>> domains(1, tmp_cd);
	int tag = -100;

	_subdivideDomains(domains, tag);

	 


	 
	if (tag == -1)
	{
		std::cout << "==============  Bezier TET appaer Flipped ================" << std::endl;
		return -1;
	}
	else if (tag == 1)
	{
		std::cout << "============== Bezier TET No Flip ================" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "============== Error: arrive at Max subdivision num ================" << std::endl;
		return 0;
	}






}




int Bezier_TeT_Injective_Checker::Tet_Order2_is_definitely_injective_by_determinant_By_Cal_Extreme(std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z)
{

	if (tet_order != 2)
	{
		std::cout << "============== Error: input Bezier Tet Order is not 2 ================" << std::endl;
		return 0; 
	}

	int order = derivative_order;
	fullVector<double>  coeffA(4);
	fullVector<double> coeffB(4);
	fullVector<double> coeffC(4);
	fullVector<double> coeffCubic;
	fullVector<double> temp_coeffCubic;
	coeffCubic.resize((3 * order + 1) * (3 * order + 2) * (3 * order + 3) / 6, true); 

	//(-uz)*vy*wx
	//(-uz)
	coeffA(0) = -2. * (_x[7] - _x[0]);
	coeffA(1) = -2. * (_x[9] - _x[4]);
	coeffA(2) = -2. * (_x[8] - _x[6]);
	coeffA(3) = -2. * (_x[3] - _x[7]);

	//vy
	coeffB(0) = 2. * (_y[6] - _y[0]);
	coeffB(1) = 2. * (_y[5] - _y[4]);
	coeffB(2) = 2. * (_y[2] - _y[6]);
	coeffB(3) = 2. * (_y[8] - _y[7]);

	//wx
	coeffC(0) = 2. * (_z[4] - _z[0]);
	coeffC(1) = 2. * (_z[1] - _z[4]);
	coeffC(2) = 2. * (_z[5] - _z[6]);
	coeffC(3) = 2. * (_z[9] - _z[7]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uy* vz *wx
	//uy
	coeffA(0) = 2. * (_x[6] - _x[0]);
	coeffA(1) = 2. * (_x[5] - _x[4]);
	coeffA(2) = 2. * (_x[2] - _x[6]);
	coeffA(3) = 2. * (_x[8] - _x[7]);

	//vz
	coeffB(0) = 2. * (_y[7] - _y[0]);
	coeffB(1) = 2. * (_y[9] - _y[4]);
	coeffB(2) = 2. * (_y[8] - _y[6]);
	coeffB(3) = 2. * (_y[3] - _y[7]);

	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uz* vx* wy
	//uz
	coeffA(0) = 2. * (_x[7] - _x[0]);
	coeffA(1) = 2. * (_x[9] - _x[4]);
	coeffA(2) = 2. * (_x[8] - _x[6]);
	coeffA(3) = 2. * (_x[3] - _x[7]);
	//vx
	coeffB(0) = 2. * (_y[4] - _y[0]);
	coeffB(1) = 2. * (_y[1] - _y[4]);
	coeffB(2) = 2. * (_y[5] - _y[6]);
	coeffB(3) = 2. * (_y[9] - _y[7]);
	//wy
	coeffC(0) = 2. * (_z[6] - _z[0]);
	coeffC(1) = 2. * (_z[5] - _z[4]);
	coeffC(2) = 2. * (_z[2] - _z[6]);
	coeffC(3) = 2. * (_z[8] - _z[7]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-ux) * vz * wy
	//-ux
	coeffA(0) = -2. * (_x[4] - _x[0]);
	coeffA(1) = -2. * (_x[1] - _x[4]);
	coeffA(2) = -2. * (_x[5] - _x[6]);
	coeffA(3) = -2. * (_x[9] - _x[7]);

	//vz
	coeffB(0) = 2. * (_y[7] - _y[0]);
	coeffB(1) = 2. * (_y[9] - _y[4]);
	coeffB(2) = 2. * (_y[8] - _y[6]);
	coeffB(3) = 2. * (_y[3] - _y[7]);

	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-uy) *vx *wz
	//-uy
	coeffA(0) = -2. * (_x[6] - _x[0]);
	coeffA(1) = -2. * (_x[5] - _x[4]);
	coeffA(2) = -2. * (_x[2] - _x[6]);
	coeffA(3) = -2. * (_x[8] - _x[7]);

	//vx
	coeffB(0) = 2. * (_y[4] - _y[0]);
	coeffB(1) = 2. * (_y[1] - _y[4]);
	coeffB(2) = 2. * (_y[5] - _y[6]);
	coeffB(3) = 2. * (_y[9] - _y[7]);

	//wz
	coeffC(0) = 2. * (_z[7] - _z[0]);
	coeffC(1) = 2. * (_z[9] - _z[4]);
	coeffC(2) = 2. * (_z[8] - _z[6]);
	coeffC(3) = 2. * (_z[3] - _z[7]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//ux *vy* wz
	//ux
	coeffA(0) = 2. * (_x[4] - _x[0]);
	coeffA(1) = 2. * (_x[1] - _x[4]);
	coeffA(2) = 2. * (_x[5] - _x[6]);
	coeffA(3) = 2. * (_x[9] - _x[7]);
	//vy
	coeffB(0) = 2. * (_y[6] - _y[0]);
	coeffB(1) = 2. * (_y[5] - _y[4]);
	coeffB(2) = 2. * (_y[2] - _y[6]);
	coeffB(3) = 2. * (_y[8] - _y[7]);
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	 
	std::shared_ptr<bezierCoeff> bez = std::make_shared<bezierCoeff>(coeffCubic, 3 * order);


	// Refine coefficients
	std::shared_ptr<_coeffDataJac> tmp_cd = std::make_shared<_coeffDataJac>(bez);
	std::vector<std::shared_ptr< _coeffData>> domains(1, tmp_cd);
	int tag = -100;
	 
	_subdivideDomains(domains, true, false, tag); 


	 
	// Get extrema
	double min = std::numeric_limits<double>::max();
	double max = -min;
	for (std::size_t i = 0; i < domains.size(); ++i) {
		min = std::min(min, domains[i]->minB());
		max = std::max(max, domains[i]->maxB());
		 
	}

	//std::cout << "======================= min: " << min << "  " << "max: " << max << " =======================" << std::endl;

	if (min > 0.) tag = 1;
	else if (max > 0.) tag = -1;
	else tag = 0;

	 
	if (tag == -1)
	{
		//std::cout << "============== Bezier TET appaer Flipped ================" << std::endl;
		return -1;
	}
	else if (tag == 1)
	{
		//std::cout << "============== Bezier TET No Flip ================" << std::endl;
		return 1;
	}
	else
	{
		//std::cout << "============== Error: arrive at Max subdivision num ================" << std::endl;
		return 0;
	}

}


int Bezier_TeT_Injective_Checker::Tet_Order2_is_definitely_injective_by_determinant (std::vector<double>& _x, std::vector<double>& _y, std::vector<double>& _z)
{

	if (tet_order != 2)
	{
		std::cout << "============== Error: input Bezier Tet Order is not 2 ================" << std::endl;
		return 0; 
	}

	int order = derivative_order;
	fullVector<double>  coeffA(4);
	fullVector<double> coeffB(4);
	fullVector<double> coeffC(4);
	fullVector<double> coeffCubic;
	fullVector<double> temp_coeffCubic;
	coeffCubic.resize((3 * order + 1) * (3 * order + 2) * (3 * order + 3) / 6, true); 

	//(-uz)*vy*wx
	//(-uz)
	coeffA(0) = -2. * (_x[7] - _x[0]);
	coeffA(1) = -2. * (_x[9] - _x[4]);
	coeffA(2) = -2. * (_x[8] - _x[6]);
	coeffA(3) = -2. * (_x[3] - _x[7]);

	//vy
	coeffB(0) = 2. * (_y[6] - _y[0]);
	coeffB(1) = 2. * (_y[5] - _y[4]);
	coeffB(2) = 2. * (_y[2] - _y[6]);
	coeffB(3) = 2. * (_y[8] - _y[7]);

	//wx
	coeffC(0) = 2. * (_z[4] - _z[0]);
	coeffC(1) = 2. * (_z[1] - _z[4]);
	coeffC(2) = 2. * (_z[5] - _z[6]);
	coeffC(3) = 2. * (_z[9] - _z[7]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uy* vz *wx
	//uy
	coeffA(0) = 2. * (_x[6] - _x[0]);
	coeffA(1) = 2. * (_x[5] - _x[4]);
	coeffA(2) = 2. * (_x[2] - _x[6]);
	coeffA(3) = 2. * (_x[8] - _x[7]);

	//vz
	coeffB(0) = 2. * (_y[7] - _y[0]);
	coeffB(1) = 2. * (_y[9] - _y[4]);
	coeffB(2) = 2. * (_y[8] - _y[6]);
	coeffB(3) = 2. * (_y[3] - _y[7]);

	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//uz* vx* wy
	//uz
	coeffA(0) = 2. * (_x[7] - _x[0]);
	coeffA(1) = 2. * (_x[9] - _x[4]);
	coeffA(2) = 2. * (_x[8] - _x[6]);
	coeffA(3) = 2. * (_x[3] - _x[7]);
	//vx
	coeffB(0) = 2. * (_y[4] - _y[0]);
	coeffB(1) = 2. * (_y[1] - _y[4]);
	coeffB(2) = 2. * (_y[5] - _y[6]);
	coeffB(3) = 2. * (_y[9] - _y[7]);
	//wy
	coeffC(0) = 2. * (_z[6] - _z[0]);
	coeffC(1) = 2. * (_z[5] - _z[4]);
	coeffC(2) = 2. * (_z[2] - _z[6]);
	coeffC(3) = 2. * (_z[8] - _z[7]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-ux) * vz * wy
	//-ux
	coeffA(0) = -2. * (_x[4] - _x[0]);
	coeffA(1) = -2. * (_x[1] - _x[4]);
	coeffA(2) = -2. * (_x[5] - _x[6]);
	coeffA(3) = -2. * (_x[9] - _x[7]);

	//vz
	coeffB(0) = 2. * (_y[7] - _y[0]);
	coeffB(1) = 2. * (_y[9] - _y[4]);
	coeffB(2) = 2. * (_y[8] - _y[6]);
	coeffB(3) = 2. * (_y[3] - _y[7]);

 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//(-uy) *vx *wz
	//-uy
	coeffA(0) = -2. * (_x[6] - _x[0]);
	coeffA(1) = -2. * (_x[5] - _x[4]);
	coeffA(2) = -2. * (_x[2] - _x[6]);
	coeffA(3) = -2. * (_x[8] - _x[7]);

	//vx
	coeffB(0) = 2. * (_y[4] - _y[0]);
	coeffB(1) = 2. * (_y[1] - _y[4]);
	coeffB(2) = 2. * (_y[5] - _y[6]);
	coeffB(3) = 2. * (_y[9] - _y[7]);

	//wz
	coeffC(0) = 2. * (_z[7] - _z[0]);
	coeffC(1) = 2. * (_z[9] - _z[4]);
	coeffC(2) = 2. * (_z[8] - _z[6]);
	coeffC(3) = 2. * (_z[3] - _z[7]);

	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

	//ux *vy* wz
	//ux
	coeffA(0) = 2. * (_x[4] - _x[0]);
	coeffA(1) = 2. * (_x[1] - _x[4]);
	coeffA(2) = 2. * (_x[5] - _x[6]);
	coeffA(3) = 2. * (_x[9] - _x[7]);
	//vy
	coeffB(0) = 2. * (_y[6] - _y[0]);
	coeffB(1) = 2. * (_y[5] - _y[4]);
	coeffB(2) = 2. * (_y[2] - _y[6]);
	coeffB(3) = 2. * (_y[8] - _y[7]);
	 
	raiser->computeCoeff(coeffA, coeffB, coeffC, temp_coeffCubic);
	coeffCubic.axpy(temp_coeffCubic);

 
	std::shared_ptr<bezierCoeff> bez = std::make_shared<bezierCoeff>(coeffCubic, 3 * order);


	// Refine coefficients
	std::shared_ptr<_coeffDataJac> tmp_cd = std::make_shared<_coeffDataJac>(bez);
	 
	std::vector<std::shared_ptr<_coeffData>> domains(1, tmp_cd);

	int tag = -100;

	 
    _subdivideDomains(domains, tag);
	 

	 
	if (tag == -1)
	{
		//std::cout << "============== Bezier TET appaer Flipped ================" << std::endl;
		return -1;
	}
	else if (tag == 1)
	{
		//std::cout << "============== Bezier TET No Flip ================" << std::endl;
		return 1;
	}
	else
	{
		//std::cout << "============== Error: arrive at Max subdivision num ================" << std::endl;
		return 0;
	}

}

 