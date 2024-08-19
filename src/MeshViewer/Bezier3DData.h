#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <Eigen/Dense>

struct Bezier3D2d
{
public:
	Eigen::MatrixXd m_V; //coordinate matrix:toal_v_num * 3
	
	Eigen::MatrixXi m_Sur_T;//Connection relationship of Bezier triangles on the surface 
	Eigen::MatrixXi m_Volume_T;//Connection relationship of Bezier tetrahedron

	int toal_v_num;//The total number of control points (including all vertices) of the Bezier tetrahedral mesh
	int sur_v_num;//The total number of vertices and control points on the Bezier tetrahedral mesh surface
	int sur_ver_num;//The total number of vertices on the Bezier tetrahedral mesh surface (excluding control points on the edges)
	int vol_v_num;//The number of vertices and control points inside the Bezier tetrahedral mesh
	int vol_ver_num;//The total number of vertices inside the Bezier tetrahedral mesh (excluding control points on the internal edges)


	int toal_f_num;//Bezier triangles of the surface plus the number of Bezier tetrahedrons
	int tri_f_num;//Number of Bezier triangles on the surface
	int tet_f_num;//Number of Bezer tetrahedrons
};

int Lower_tri_ijtoIndex(int i, int j, int n);
 
void convert_to_my_data(std::string input, std::string output);

void convert_part(std::string input, std::string output);

void read_get_Data(Bezier3D2d& d_, std::string s);

void read_get_Data_for_Bezier(Bezier3D2d& d_, std::string s);

void read_get_Data(Eigen::MatrixXd& target_V, std::string s);

void write_curve_mesh(std::string& filename, Bezier3D2d& d_, Eigen::VectorXd& position_of_mesh);

void write_3D_msh(std::string& filename, Bezier3D2d& d_, Eigen::VectorXd& position_of_mesh);

void write_3D_msh_Lagrange(std::string& filename, Bezier3D2d& d_, Eigen::VectorXd& position_of_mesh);
 

std::string indent(int depth);

int offset(int i, int j);

 


 

 

 

 

 