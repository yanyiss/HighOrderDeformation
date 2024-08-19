#pragma once
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "Bezier3DData.h"
#include "PardisoSolver.h"
#include <time.h>
#include<queue>
#include "../src/BezierTet/Bezier_TeT_Injective_Checker.h"

using namespace Eigen;
using namespace std;

 
class Deformation
{
public:
	Deformation()
	{
		pardiso = nullptr;
		bezier_checker = nullptr;

	}

	~Deformation()
	{
		delete pardiso;
		delete bezier_checker;

	}
public:
	void init();
	void Pre_calculate();
	void Generate_control_mesh();
	void Uniform_Sampling_On_Parameter_Domain();

	 
	void Cal_metric_source_OMP();

	 
	void Optimization_OMP(); 
	void Optimization_OMP_with_cut(); 
	 
	bool is_equal(double& x, double& y);

	void max_step(const VectorXd& xy, const VectorXd& dd, double& step);
	double get_smallest_pos_quad_zero(double a, double b, double c, double d);
	double get_smallest_pos_quad_zero(double a, double b, double c);
	double mypow(double &x,double &y);
	double cubic_root_pow(double& x); 

	 
	void Energy_OMP(VectorXd& position, double& energyupdate);


	//void backtracking_line_search(VectorXd& x, const VectorXd& d, const VectorXd& negetive_grad, double& alpha);
	void backtracking_line_search_OMP(VectorXd& x, const VectorXd& d, const VectorXd& negetive_grad, double& alpha);
	void get_valid_step(VectorXd& x, const VectorXd& d, double& alpha);
	void No_flip_mesh(VectorXd& x, const VectorXd& d, double& alpha);//find alpha to make Bezier mesh regular
	int check_flip(VectorXd& x, const VectorXd& d, double& alpha);

	void check_source_flip();

public:
	 
	bool source_Bezier_mesh_injective = false;

	double fixed_total_energy; 
	double fixed_last_total_energy;


	bool is_need_self_adaptation_sampling_Parameter_Domain = false; 

	double lamda1 = 1000000.0;//The weight of the squared distance energy,The default may need to be larger
	double lamda2 = 1000000.0; 
	double lamda3 = 1000000.0;
	int fixed_id1 = 779 ; // 
	int fixed_id2 = 807  ; // 
	int fixed_id3 = 790;// 


	//spare
	double lamda4 = 100.0;
	int fixed_id4 = 499; 
	bool is_use_fixed = false;

	//The following is the handle used for movement
	double miu = 1000.0;//The weight of the moved vertex(handle to morphing)    
	double miu1 =000.0;
	 
	int move_vertex_ID = 718;  
	double move_vertex_x;      
	double move_vertex_y;      
	double move_vertex_z;

	int move_vertex_ID1 = 514;   
	double move_vertex_x1;      
	double move_vertex_y1;
	double move_vertex_z1;

	//The following mobile handle is a spare.
	double miu2 = 1000000.0;
	int move_vertex_ID2 = 539; 
	double move_vertex_x2;
	double move_vertex_y2;
	double move_vertex_z2;
	bool is_use_move = false;
public: 
	double total_energy;
	double last_total_energy;

	double cur_gradient_norm = 1e8;

	Bezier3D2d  d_;
	 
	int Tet_N;//total Bezier mesh tetrahedron num
	int V_N;//total Bezier mesh vertex num(include control points)
	vector<int> F0;//on every Bezier tetrahedron,index of the first control point,that is Index of b1
	vector<int> F1;
	vector<int> F2;
	vector<int> F3;
	vector<int> F4;
	vector<int> F5;
	vector<int> F6;
	vector<int> F7;
	vector<int> F8;
	vector<int> F9;
	VectorXd position_of_mesh;//that is coordinate of  all vertex(include control points)
	/*  the  represent of position_of_mesh:
		x 0
	*   ...
	*   x V_N-1
		y 0
		...
		y V_N-1
		z 0
		...
		z V_N-1
	*/
	bool is_search_direction_error = false;
	bool is_exist_Bezier_triangle_flip = false; 
	bool is_Eigenvalues_order_error1 = false;
	bool is_Eigenvalues_order_error2 = false;
	bool is_Eigenvalues_order_error3 = false;


	//It is only required that the four straight-sided tetrahedrons at the corner points of the Bezier tetrahedron should not be flipped.
	Eigen::MatrixXi control_T;//contol_net mesh,control tetrahedron num*4
	/*vi are vertex and control points id,coordinate data in d_.m_V
	 v1,v2,v3,v4
	* ......
	* v5,v6,v7,v8
	*/

	std::vector<std::vector<double>> metric_source_g1;//J0^TJ0 
	std::vector<std::vector<double>> metric_source_g2;
	std::vector<std::vector<double>> metric_source_g3;
	std::vector<std::vector<double>> metric_source_g4;
	std::vector<std::vector<double>> metric_source_g5;
	std::vector<std::vector<double>> metric_source_g6;

 
	std::vector<std::vector<double>> reference_x_On_Volume; 
	std::vector<std::vector<double>> reference_y_On_Volume;
	std::vector<std::vector<double>> reference_z_On_Volume;


	 
	std::vector<double> Fix_reference_x;
	std::vector<double> Fix_reference_y;
	std::vector<double> Fix_reference_z;


private:
	PardisoSolver* pardiso;
	vector<int> pardiso_ia;
	vector<int> pardiso_ja;
	vector<double> pardiso_a;
	vector<double> pardiso_b;

	vector<int> id_h0_0; vector<int> id_h0_1; vector<int> id_h0_2; vector<int> id_h0_3; vector<int> id_h0_4; vector<int> id_h0_5; vector<int> id_h0_6; vector<int> id_h0_7; vector<int> id_h0_8; vector<int> id_h0_9; vector<int> id_h0_10; vector<int> id_h0_11; vector<int> id_h0_12; vector<int> id_h0_13; vector<int> id_h0_14; vector<int> id_h0_15; vector<int> id_h0_16; vector<int> id_h0_17; vector<int> id_h0_18; vector<int> id_h0_19; vector<int> id_h0_20; vector<int> id_h0_21; vector<int> id_h0_22; vector<int> id_h0_23; vector<int> id_h0_24; vector<int> id_h0_25; vector<int> id_h0_26; vector<int> id_h0_27; vector<int> id_h0_28; vector<int> id_h0_29;
	vector<int> id_h1_1; vector<int> id_h1_2; vector<int> id_h1_3; vector<int> id_h1_4; vector<int> id_h1_5; vector<int> id_h1_6; vector<int> id_h1_7; vector<int> id_h1_8; vector<int> id_h1_9; vector<int> id_h1_10; vector<int> id_h1_11; vector<int> id_h1_12; vector<int> id_h1_13; vector<int> id_h1_14; vector<int> id_h1_15; vector<int> id_h1_16; vector<int> id_h1_17; vector<int> id_h1_18; vector<int> id_h1_19; vector<int> id_h1_20; vector<int> id_h1_21; vector<int> id_h1_22; vector<int> id_h1_23; vector<int> id_h1_24; vector<int> id_h1_25; vector<int> id_h1_26; vector<int> id_h1_27; vector<int> id_h1_28; vector<int> id_h1_29;
	vector<int> id_h2_2; vector<int> id_h2_3; vector<int> id_h2_4; vector<int> id_h2_5; vector<int> id_h2_6; vector<int> id_h2_7; vector<int> id_h2_8; vector<int> id_h2_9; vector<int> id_h2_10; vector<int> id_h2_11; vector<int> id_h2_12; vector<int> id_h2_13; vector<int> id_h2_14; vector<int> id_h2_15; vector<int> id_h2_16; vector<int> id_h2_17; vector<int> id_h2_18; vector<int> id_h2_19; vector<int> id_h2_20; vector<int> id_h2_21; vector<int> id_h2_22; vector<int> id_h2_23; vector<int> id_h2_24; vector<int> id_h2_25; vector<int> id_h2_26; vector<int> id_h2_27; vector<int> id_h2_28; vector<int> id_h2_29;
	vector<int> id_h3_3; vector<int> id_h3_4; vector<int> id_h3_5; vector<int> id_h3_6; vector<int> id_h3_7; vector<int> id_h3_8; vector<int> id_h3_9; vector<int> id_h3_10; vector<int> id_h3_11; vector<int> id_h3_12; vector<int> id_h3_13; vector<int> id_h3_14; vector<int> id_h3_15; vector<int> id_h3_16; vector<int> id_h3_17; vector<int> id_h3_18; vector<int> id_h3_19; vector<int> id_h3_20; vector<int> id_h3_21; vector<int> id_h3_22; vector<int> id_h3_23; vector<int> id_h3_24; vector<int> id_h3_25; vector<int> id_h3_26; vector<int> id_h3_27; vector<int> id_h3_28; vector<int> id_h3_29;
	vector<int> id_h4_4; vector<int> id_h4_5; vector<int> id_h4_6; vector<int> id_h4_7; vector<int> id_h4_8; vector<int> id_h4_9; vector<int> id_h4_10; vector<int> id_h4_11; vector<int> id_h4_12; vector<int> id_h4_13; vector<int> id_h4_14; vector<int> id_h4_15; vector<int> id_h4_16; vector<int> id_h4_17; vector<int> id_h4_18; vector<int> id_h4_19; vector<int> id_h4_20; vector<int> id_h4_21; vector<int> id_h4_22; vector<int> id_h4_23; vector<int> id_h4_24; vector<int> id_h4_25; vector<int> id_h4_26; vector<int> id_h4_27; vector<int> id_h4_28; vector<int> id_h4_29;
	vector<int> id_h5_5; vector<int> id_h5_6; vector<int> id_h5_7; vector<int> id_h5_8; vector<int> id_h5_9; vector<int> id_h5_10; vector<int> id_h5_11; vector<int> id_h5_12; vector<int> id_h5_13; vector<int> id_h5_14; vector<int> id_h5_15; vector<int> id_h5_16; vector<int> id_h5_17; vector<int> id_h5_18; vector<int> id_h5_19; vector<int> id_h5_20; vector<int> id_h5_21; vector<int> id_h5_22; vector<int> id_h5_23; vector<int> id_h5_24; vector<int> id_h5_25; vector<int> id_h5_26; vector<int> id_h5_27; vector<int> id_h5_28; vector<int> id_h5_29;
	vector<int> id_h6_6; vector<int> id_h6_7; vector<int> id_h6_8; vector<int> id_h6_9; vector<int> id_h6_10; vector<int> id_h6_11; vector<int> id_h6_12; vector<int> id_h6_13; vector<int> id_h6_14; vector<int> id_h6_15; vector<int> id_h6_16; vector<int> id_h6_17; vector<int> id_h6_18; vector<int> id_h6_19; vector<int> id_h6_20; vector<int> id_h6_21; vector<int> id_h6_22; vector<int> id_h6_23; vector<int> id_h6_24; vector<int> id_h6_25; vector<int> id_h6_26; vector<int> id_h6_27; vector<int> id_h6_28; vector<int> id_h6_29;
	vector<int> id_h7_7; vector<int> id_h7_8; vector<int> id_h7_9; vector<int> id_h7_10; vector<int> id_h7_11; vector<int> id_h7_12; vector<int> id_h7_13; vector<int> id_h7_14; vector<int> id_h7_15; vector<int> id_h7_16; vector<int> id_h7_17; vector<int> id_h7_18; vector<int> id_h7_19; vector<int> id_h7_20; vector<int> id_h7_21; vector<int> id_h7_22; vector<int> id_h7_23; vector<int> id_h7_24; vector<int> id_h7_25; vector<int> id_h7_26; vector<int> id_h7_27; vector<int> id_h7_28; vector<int> id_h7_29;
	vector<int> id_h8_8; vector<int> id_h8_9; vector<int> id_h8_10; vector<int> id_h8_11; vector<int> id_h8_12; vector<int> id_h8_13; vector<int> id_h8_14; vector<int> id_h8_15; vector<int> id_h8_16; vector<int> id_h8_17; vector<int> id_h8_18; vector<int> id_h8_19; vector<int> id_h8_20; vector<int> id_h8_21; vector<int> id_h8_22; vector<int> id_h8_23; vector<int> id_h8_24; vector<int> id_h8_25; vector<int> id_h8_26; vector<int> id_h8_27; vector<int> id_h8_28; vector<int> id_h8_29;
	vector<int> id_h9_9; vector<int> id_h9_10; vector<int> id_h9_11; vector<int> id_h9_12; vector<int> id_h9_13; vector<int> id_h9_14; vector<int> id_h9_15; vector<int> id_h9_16; vector<int> id_h9_17; vector<int> id_h9_18; vector<int> id_h9_19; vector<int> id_h9_20; vector<int> id_h9_21; vector<int> id_h9_22; vector<int> id_h9_23; vector<int> id_h9_24; vector<int> id_h9_25; vector<int> id_h9_26; vector<int> id_h9_27; vector<int> id_h9_28; vector<int> id_h9_29;
	vector<int> id_h10_10; vector<int> id_h10_11; vector<int> id_h10_12; vector<int> id_h10_13; vector<int> id_h10_14; vector<int> id_h10_15; vector<int> id_h10_16; vector<int> id_h10_17; vector<int> id_h10_18; vector<int> id_h10_19; vector<int> id_h10_20; vector<int> id_h10_21; vector<int> id_h10_22; vector<int> id_h10_23; vector<int> id_h10_24; vector<int> id_h10_25; vector<int> id_h10_26; vector<int> id_h10_27; vector<int> id_h10_28; vector<int> id_h10_29;
	vector<int> id_h11_11; vector<int> id_h11_12; vector<int> id_h11_13; vector<int> id_h11_14; vector<int> id_h11_15; vector<int> id_h11_16; vector<int> id_h11_17; vector<int> id_h11_18; vector<int> id_h11_19; vector<int> id_h11_20; vector<int> id_h11_21; vector<int> id_h11_22; vector<int> id_h11_23; vector<int> id_h11_24; vector<int> id_h11_25; vector<int> id_h11_26; vector<int> id_h11_27; vector<int> id_h11_28; vector<int> id_h11_29;
	vector<int> id_h12_12; vector<int> id_h12_13; vector<int> id_h12_14; vector<int> id_h12_15; vector<int> id_h12_16; vector<int> id_h12_17; vector<int> id_h12_18; vector<int> id_h12_19; vector<int> id_h12_20; vector<int> id_h12_21; vector<int> id_h12_22; vector<int> id_h12_23; vector<int> id_h12_24; vector<int> id_h12_25; vector<int> id_h12_26; vector<int> id_h12_27; vector<int> id_h12_28; vector<int> id_h12_29;
	vector<int> id_h13_13; vector<int> id_h13_14; vector<int> id_h13_15; vector<int> id_h13_16; vector<int> id_h13_17; vector<int> id_h13_18; vector<int> id_h13_19; vector<int> id_h13_20; vector<int> id_h13_21; vector<int> id_h13_22; vector<int> id_h13_23; vector<int> id_h13_24; vector<int> id_h13_25; vector<int> id_h13_26; vector<int> id_h13_27; vector<int> id_h13_28; vector<int> id_h13_29;
	vector<int> id_h14_14; vector<int> id_h14_15; vector<int> id_h14_16; vector<int> id_h14_17; vector<int> id_h14_18; vector<int> id_h14_19; vector<int> id_h14_20; vector<int> id_h14_21; vector<int> id_h14_22; vector<int> id_h14_23; vector<int> id_h14_24; vector<int> id_h14_25; vector<int> id_h14_26; vector<int> id_h14_27; vector<int> id_h14_28; vector<int> id_h14_29;
	vector<int> id_h15_15; vector<int> id_h15_16; vector<int> id_h15_17; vector<int> id_h15_18; vector<int> id_h15_19; vector<int> id_h15_20; vector<int> id_h15_21; vector<int> id_h15_22; vector<int> id_h15_23; vector<int> id_h15_24; vector<int> id_h15_25; vector<int> id_h15_26; vector<int> id_h15_27; vector<int> id_h15_28; vector<int> id_h15_29;
	vector<int> id_h16_16; vector<int> id_h16_17; vector<int> id_h16_18; vector<int> id_h16_19; vector<int> id_h16_20; vector<int> id_h16_21; vector<int> id_h16_22; vector<int> id_h16_23; vector<int> id_h16_24; vector<int> id_h16_25; vector<int> id_h16_26; vector<int> id_h16_27; vector<int> id_h16_28; vector<int> id_h16_29;
	vector<int> id_h17_17; vector<int> id_h17_18; vector<int> id_h17_19; vector<int> id_h17_20; vector<int> id_h17_21; vector<int> id_h17_22; vector<int> id_h17_23; vector<int> id_h17_24; vector<int> id_h17_25; vector<int> id_h17_26; vector<int> id_h17_27; vector<int> id_h17_28; vector<int> id_h17_29;
	vector<int> id_h18_18; vector<int> id_h18_19; vector<int> id_h18_20; vector<int> id_h18_21; vector<int> id_h18_22; vector<int> id_h18_23; vector<int> id_h18_24; vector<int> id_h18_25; vector<int> id_h18_26; vector<int> id_h18_27; vector<int> id_h18_28; vector<int> id_h18_29;
	vector<int> id_h19_19; vector<int> id_h19_20; vector<int> id_h19_21; vector<int> id_h19_22; vector<int> id_h19_23; vector<int> id_h19_24; vector<int> id_h19_25; vector<int> id_h19_26; vector<int> id_h19_27; vector<int> id_h19_28; vector<int> id_h19_29;
	vector<int> id_h20_20; vector<int> id_h20_21; vector<int> id_h20_22; vector<int> id_h20_23; vector<int> id_h20_24; vector<int> id_h20_25; vector<int> id_h20_26; vector<int> id_h20_27; vector<int> id_h20_28; vector<int> id_h20_29;
	vector<int> id_h21_21; vector<int> id_h21_22; vector<int> id_h21_23; vector<int> id_h21_24; vector<int> id_h21_25; vector<int> id_h21_26; vector<int> id_h21_27; vector<int> id_h21_28; vector<int> id_h21_29;
	vector<int> id_h22_22; vector<int> id_h22_23; vector<int> id_h22_24; vector<int> id_h22_25; vector<int> id_h22_26; vector<int> id_h22_27; vector<int> id_h22_28; vector<int> id_h22_29;
	vector<int> id_h23_23; vector<int> id_h23_24; vector<int> id_h23_25; vector<int> id_h23_26; vector<int> id_h23_27; vector<int> id_h23_28; vector<int> id_h23_29;
	vector<int> id_h24_24; vector<int> id_h24_25; vector<int> id_h24_26; vector<int> id_h24_27; vector<int> id_h24_28; vector<int> id_h24_29;
	vector<int> id_h25_25; vector<int> id_h25_26; vector<int> id_h25_27; vector<int> id_h25_28; vector<int> id_h25_29;
	vector<int> id_h26_26; vector<int> id_h26_27; vector<int> id_h26_28; vector<int> id_h26_29;
	vector<int> id_h27_27; vector<int> id_h27_28; vector<int> id_h27_29;
	vector<int> id_h28_28; vector<int> id_h28_29;
	vector<int> id_h29_29;


	SparseMatrix<int> find_id_in_rows;

	int dim = 3;

private:
	 
	const double Parameter_Domain_eps = 1e-3;
	int Parameter_Domain_sample_num_xy = 10; 
private:
		Bezier_TeT_Injective_Checker* bezier_checker;
};