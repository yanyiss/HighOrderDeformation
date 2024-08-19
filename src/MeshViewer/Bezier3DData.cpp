#include"Bezier3DData.h"
#include<unordered_map>

double sqrt_3 = std::sqrt(3.0);
double sqrt_2 = std::sqrt(2.0);
unsigned int  indentWidth = 2;
char indentChar = ' ';
const int baseOffset = 1; // 0 index is forbidden in MSH format

std::string indent(int depth)
{
	return std::string(indentWidth * depth, indentChar);
}

int offset(int i, int j)
{
	return i + j;
}

void convert_part(std::string input, std::string output)
{
	std::ifstream ifs(input);
	if (!ifs.is_open())
	{
		std::cerr << "Error: cannot load control points from file " << input << std::endl;
		return;
	}

	std::ofstream out(output);
	out.precision(16);

	int sur_total_num;
	ifs >> sur_total_num;
	
	int sur_ver_num;
	ifs >> sur_ver_num;

	Eigen::MatrixXd initial_V;
	initial_V.resize(sur_total_num, 3);

	for (int i = 0; i < sur_total_num; i++)
	{
		ifs >> initial_V(i, 0) >> initial_V(i, 1) >> initial_V(i, 2);

	}

	int sur_tri_num;
	ifs >> sur_tri_num;

	Eigen::MatrixXi before_sur_Tri;
	before_sur_Tri.resize(sur_tri_num, 6);

	for (int i = 0; i < sur_tri_num; i++)
	{
		ifs >> before_sur_Tri(i, 0) >> before_sur_Tri(i, 1) >> before_sur_Tri(i, 2) >> before_sur_Tri(i, 3) >> before_sur_Tri(i, 4) >> before_sur_Tri(i, 5);
		for (int j = 0; j < 6; j++)
		{
			before_sur_Tri(i, j) -= 1;
		}
	}
	
	int target_sur_tri_num;
	ifs >> target_sur_tri_num;

	Eigen::MatrixXi target_sur_Tri;
	target_sur_Tri.resize(target_sur_tri_num, 6);

	for (int i = 0; i < target_sur_tri_num; i++)
	{
		ifs >> target_sur_Tri(i, 0) >> target_sur_Tri(i, 1) >> target_sur_Tri(i, 2) >> target_sur_Tri(i, 3) >> target_sur_Tri(i, 4) >> target_sur_Tri(i, 5);
		for (int j = 0; j < 6; j++)
		{
			target_sur_Tri(i, j) -= 1;
		}
	}
	ifs.close();

	std::unordered_map<int, int> hmap;
	 
	int Lower_tri_n = sur_total_num;
	int toIndex = 0; 
	int before_Tet_i = 0; 
	int before_Tet_j = 0;

	 
	for (int i = 0; i < sur_tri_num; i++)
	{
		int b0 = before_sur_Tri(i, 0); 
		int b1 = before_sur_Tri(i, 1);
		int b2 = before_sur_Tri(i, 2);
		int b3 = before_sur_Tri(i, 3);
		int b4 = before_sur_Tri(i, 4);
		int b5 = before_sur_Tri(i, 5);

		if (b0 > b1) 
		{
			before_Tet_i = b0;
			before_Tet_j = b1;
		}
		else
		{
			before_Tet_i = b1; 
			before_Tet_j = b0;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{

		}
		else 
		{
			hmap[toIndex] = b3; 
		}

		 
		if (b1 > b2) 
		{
			before_Tet_i = b1;
			before_Tet_j = b2;
		}
		else
		{
			before_Tet_i = b2;
			before_Tet_j = b1;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{

		}
		else
		{
			hmap[toIndex] = b4;// 
		}
		//------------------------------------------- 
		if (b2 > b0) 
		{
			before_Tet_i = b2;
			before_Tet_j = b0;
		}
		else
		{
			before_Tet_i = b0;
			before_Tet_j = b2;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{

		}
		else
		{
			hmap[toIndex] = b5; 
		}
		//-----------------------

	}

	 
	Eigen::MatrixXd target_V;
	target_V.resize(sur_total_num, 3);

	for (int i = 0; i < sur_ver_num; i++)
	{
		target_V.row(i) = initial_V.row(i);
	}

	for (int i = 0; i < target_sur_tri_num; i++)
	{
		int b0 = target_sur_Tri(i, 0); 
		int b1 = target_sur_Tri(i, 1);
		int b2 = target_sur_Tri(i, 2);
		int b3 = target_sur_Tri(i, 3);
		int b4 = target_sur_Tri(i, 4);
		int b5 = target_sur_Tri(i, 5);

		if (b0 > b1) 
		{
			before_Tet_i = b0;
			before_Tet_j = b1;
		}
		else
		{
			before_Tet_i = b1; 
			before_Tet_j = b0;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{
			 
			target_V.row(b3) = 0.9 * (initial_V.row(b0) + initial_V.row(b1)) / 2 + 0.1 * initial_V.row(hmap[toIndex]);
		}
		else
		{
			std::cout << "################## error ################" << std::endl;
		}


		//------------------------------------------- 
		if (b1 > b2) 
		{
			before_Tet_i = b1;
			before_Tet_j = b2;
		}
		else
		{
			before_Tet_i = b2;
			before_Tet_j = b1;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{
			 
			target_V.row(b4) = 0.9 * (initial_V.row(b1) + initial_V.row(b2)) / 2 + 0.1 * initial_V.row(hmap[toIndex]);

		}
		else
		{
			std::cout << "################## error ################" << std::endl;

		}

		//------------------------------------------- 
		if (b2 > b0) 
		{
			before_Tet_i = b2;
			before_Tet_j = b0;
		}
		else
		{
			before_Tet_i = b0;
			before_Tet_j = b2;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{
			 
			target_V.row(b5) = 0.9 * (initial_V.row(b2) + initial_V.row(b0)) / 2 + 0.1 * initial_V.row(hmap[toIndex]);

		} 
		else
		{
			std::cout << "################## error ################" << std::endl;

		}
		//-----------------------
	}

	 
	for (int i = 0; i < sur_total_num; i++)
	{
		out << target_V(i, 0) << "  " << target_V(i, 1) << " " << target_V(i, 2) << '\n';
	}
	out << std::endl;
}


 
void convert_to_my_data(std::string input, std::string output)
{
	bool is_interior_linear_tet = false; 
	std::ifstream ifs(input);
	if (!ifs.is_open())
	{
		std::cerr << "Error: cannot load control points from file " << input << std::endl;
		return;
	}

	std::ofstream out(output);
	out.precision(16);

	int toal_v_num; 
	ifs >> toal_v_num;
	std::cout << "toal_v_num is: " << toal_v_num << std::endl;

	int sur_ver_num; 
	ifs >> sur_ver_num;
	std::cout << "sur_ver_num is: " << sur_ver_num << std::endl;

	int sur_ctp_num; 
	ifs >> sur_ctp_num;
	std::cout << "sur_ctp_num is: " << sur_ctp_num << std::endl;

	int interior_ver_num; 
	ifs >> interior_ver_num;
	std::cout << "interior_ver_num is: " << interior_ver_num << std::endl;

	int interior_ctp_num = toal_v_num - sur_ver_num - sur_ctp_num - interior_ver_num; 
	std::cout << "interior_ctp_num is: " << interior_ctp_num << std::endl;

	Eigen::MatrixXd initial_V; 
	initial_V.resize(toal_v_num, 3);
	
	for (int i = 0; i < toal_v_num; i++) {
		ifs >> initial_V(i, 0) >> initial_V(i, 1) >> initial_V(i, 2);
		 
	}

	printf("====== is %.26f ===========:", initial_V(26, 2));

	int sur_tri_num;
	ifs >> sur_tri_num;

	Eigen::MatrixXi before_sur_Tri; 
	before_sur_Tri.resize(sur_tri_num, 3);
	for (int i = 0; i < sur_tri_num; i++) {
		ifs >> before_sur_Tri(i, 0) >> before_sur_Tri(i, 1) >> before_sur_Tri(i, 2); 
		before_sur_Tri(i, 0) -= 1;
		before_sur_Tri(i, 1) -= 1;
		before_sur_Tri(i, 2) -= 1;
	}

	int tet_num; 
	ifs >> tet_num;
	Eigen::MatrixXi before_volume_Tet; 
	before_volume_Tet.resize(tet_num, 10);

	for (int i = 0; i < tet_num; i++) {
		ifs >> before_volume_Tet(i, 0) >> before_volume_Tet(i, 1) >> before_volume_Tet(i, 2) >> before_volume_Tet(i, 3) >> before_volume_Tet(i, 4) >> before_volume_Tet(i, 5)
			>> before_volume_Tet(i, 6) >> before_volume_Tet(i, 7) >> before_volume_Tet(i, 8) >> before_volume_Tet(i, 9);
		for (int j = 0; j < 10; j++) {
			before_volume_Tet(i, j) -= 1; 
		}
	}

	ifs.close();


	 
	Eigen::MatrixXd my_target_V; 
	my_target_V.resize(toal_v_num, 3);

	 
	int sur_ver_cout = 0; 
	int sur_ctp_cout = sur_ver_num; 
	int interior_ver_cout = sur_ver_num + sur_ctp_num; 
	int interior_ctp_cout = sur_ver_num + sur_ctp_num + interior_ver_num; 

	std::vector<int> flag_for_initial_V(toal_v_num, -1); 
	//0:sur_ver  1:sur_ctp  2:interior_ver  3:interior_ctp
	std::vector<int> initial_V_to_target_V_ID(toal_v_num, -1); 

	std::unordered_map<int, int> hmap; 

	 
	int Lower_tri_n = toal_v_num;
	std::cout << "Lower_tri_n is: " << Lower_tri_n << std::endl;
	int toIndex = 0; 
	int before_Tet_i = 0; 
	int before_Tet_j = 0;


	Eigen::MatrixXi my_sur_Tri; 
	my_sur_Tri.resize(sur_tri_num, 6); 

	Eigen::MatrixXi my_volume_Tet; 
	my_volume_Tet.resize(tet_num, 10);

	 
	for (int i = 0; i < sur_tri_num; i++)
	{
		int b0 = before_sur_Tri(i, 0);
		int b1 = before_sur_Tri(i, 1);
		int b2 = before_sur_Tri(i, 2);

		if (flag_for_initial_V[b0] == -1)
		{
			initial_V_to_target_V_ID[b0] = sur_ver_cout; 
			my_target_V.row(sur_ver_cout) = initial_V.row(b0); 
			sur_ver_cout++;

			flag_for_initial_V[b0] = 0; 		 
		}
		my_sur_Tri(i, 0) = initial_V_to_target_V_ID[b0]; 

		if (flag_for_initial_V[b1] == -1)
		{
			initial_V_to_target_V_ID[b1] = sur_ver_cout; 
			my_target_V.row(sur_ver_cout) = initial_V.row(b1); 
			sur_ver_cout++;

			flag_for_initial_V[b1] = 0; 		 

		}
		my_sur_Tri(i, 1) = initial_V_to_target_V_ID[b1]; 

		if (flag_for_initial_V[b2] == -1)
		{
			initial_V_to_target_V_ID[b2] = sur_ver_cout; 
			my_target_V.row(sur_ver_cout) = initial_V.row(b2); 
			sur_ver_cout++;

			flag_for_initial_V[b2] = 0; 		 
		}
		my_sur_Tri(i, 2) = initial_V_to_target_V_ID[b2]; 

		 
		if (b0 > b1) 
		{
			before_Tet_i = b0;
			before_Tet_j = b1;
		}
		else
		{
			before_Tet_i = b1; 
			before_Tet_j = b0;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n); 
		if (toIndex == 10158) { std::cout << "b0 b1 duandian is: " << b0 << " " << b1 << std::endl; 
		std::cout << "before_Tet_i before_Tet_j duandian is: " << before_Tet_i  << " " << before_Tet_j << std::endl;
		std::cout << Lower_tri_ijtoIndex(124, 116, 144) << std::endl;
		}

		if (hmap.find(toIndex) != hmap.end()) 
		{

		}
		else 
		{
			hmap[toIndex] = -1; 
		}
		//------------------------------------------- 
		if (b1 > b2) 
		{
			before_Tet_i = b1;
			before_Tet_j = b2;
		}
		else
		{
			before_Tet_i = b2;
			before_Tet_j = b1;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);
		 
		if (hmap.find(toIndex) != hmap.end()) 
		{

		}
		else
		{
			hmap[toIndex] = -1; 
		}
		//------------------------------------------- 
		if (b2 > b0) 
		{
			before_Tet_i = b2;
			before_Tet_j = b0;
		}
		else
		{
			before_Tet_i = b0;
			before_Tet_j = b2;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);
		if (toIndex == 10158) std::cout << "b2 b0 duandian is: " << b2 << " " << b0 << std::endl;

		if (hmap.find(toIndex) != hmap.end()) 
		{

		}
		else
		{
			hmap[toIndex] = -1; 
		}

		 

	}

	 
	 
	for (int i = 0; i < tet_num; i++) 
	{
		int b1  = before_volume_Tet(i, 0); 
		int b2  = before_volume_Tet(i, 1);
		int b3 =  before_volume_Tet(i, 2);
		int b4 =  before_volume_Tet(i, 3);
		int b5 =  before_volume_Tet(i, 4);
		int b6 =  before_volume_Tet(i, 5);
		int b7 =  before_volume_Tet(i, 6);
		int b8 =  before_volume_Tet(i, 7);
		int b9 =  before_volume_Tet(i, 8);
		int b10 = before_volume_Tet(i, 9);

		 
		 
		//------------------------ 
		if (b1 > b2)
		{
			before_Tet_i = b1;
			before_Tet_j = b2;
		}
		else
		{
			before_Tet_i = b2; 
			before_Tet_j = b1;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{
			if (flag_for_initial_V[b5] == -1) 
			{
				initial_V_to_target_V_ID[b5] = sur_ctp_cout; 
				my_target_V.row(sur_ctp_cout) = initial_V.row(b5);
				hmap[toIndex] = sur_ctp_cout; 
				sur_ctp_cout++;

				flag_for_initial_V[b5] = 1; 
			}
		}
		else 
		{
			if (flag_for_initial_V[b5] == -1) 
			{
				initial_V_to_target_V_ID[b5] = interior_ctp_cout;
				my_target_V.row(interior_ctp_cout) = initial_V.row(b5);
				if (is_interior_linear_tet) 
				{
					my_target_V.row(interior_ctp_cout) = (initial_V.row(b1) + initial_V.row(b2)) / 2;
				}
				interior_ctp_cout++;

				flag_for_initial_V[b5] = 3; 
			}

		}

		//----------------------- 
		if (b2 > b3)
		{
			before_Tet_i = b2;
			before_Tet_j = b3;
		}
		else
		{
			before_Tet_i = b3; 
			before_Tet_j = b2;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);
		if (hmap.find(toIndex) != hmap.end()) 
		{
			if (flag_for_initial_V[b6] == -1) 
			{
				initial_V_to_target_V_ID[b6] = sur_ctp_cout; 
				my_target_V.row(sur_ctp_cout) = initial_V.row(b6); 
				hmap[toIndex] = sur_ctp_cout; 
				sur_ctp_cout++;

				flag_for_initial_V[b6] = 1; 

			}

		}
		else 
		{
			if (flag_for_initial_V[b6] == -1) 
			{
				initial_V_to_target_V_ID[b6] = interior_ctp_cout;
				my_target_V.row(interior_ctp_cout) = initial_V.row(b6);
				if (is_interior_linear_tet) 
				{
					my_target_V.row(interior_ctp_cout) = (initial_V.row(b2) + initial_V.row(b3)) / 2;
				}
				interior_ctp_cout++;

				flag_for_initial_V[b6] = 3; 
			}
		}
	
		//----------------------- 
		if (b3 > b1)
		{
			before_Tet_i = b3;
			before_Tet_j = b1;
		}
		else
		{
			before_Tet_i = b1; 
			before_Tet_j = b3;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);
		if (hmap.find(toIndex) != hmap.end()) 
		{
			if (flag_for_initial_V[b7] == -1) 
			{
				initial_V_to_target_V_ID[b7] = sur_ctp_cout; 
				my_target_V.row(sur_ctp_cout) = initial_V.row(b7); 
				hmap[toIndex] = sur_ctp_cout; 
				sur_ctp_cout++;

				flag_for_initial_V[b7] = 1; 

			}



		}
		else 
		{
			if (flag_for_initial_V[b7] == -1) 
			{
				initial_V_to_target_V_ID[b7] = interior_ctp_cout;
				my_target_V.row(interior_ctp_cout) = initial_V.row(b7);
				if (is_interior_linear_tet) 
				{
					my_target_V.row(interior_ctp_cout) = (initial_V.row(b3) + initial_V.row(b1)) / 2;
				}
				interior_ctp_cout++;

				flag_for_initial_V[b7] = 3; 
			}


		}


		//----------------------- 
		if (b1 > b4)
		{
			before_Tet_i = b1;
			before_Tet_j = b4;
		}
		else
		{
			before_Tet_i = b4; 
			before_Tet_j = b1;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{
			if (flag_for_initial_V[b8] == -1) 
			{
				initial_V_to_target_V_ID[b8] = sur_ctp_cout; 
				my_target_V.row(sur_ctp_cout) = initial_V.row(b8); 
				hmap[toIndex] = sur_ctp_cout; 
				sur_ctp_cout++;

				flag_for_initial_V[b8] = 1; 

			}



		}
		else 
		{
			if (flag_for_initial_V[b8] == -1) 
			{
				initial_V_to_target_V_ID[b8] = interior_ctp_cout;
				my_target_V.row(interior_ctp_cout) = initial_V.row(b8);
				if (is_interior_linear_tet) 
				{
					my_target_V.row(interior_ctp_cout) = (initial_V.row(b1) + initial_V.row(b4)) / 2;
				}
				interior_ctp_cout++;

				flag_for_initial_V[b8] = 3; 
			}


		}

		//----------------------- 
		if (b3 > b4)
		{
			before_Tet_i = b3;
			before_Tet_j = b4;
		}
		else
		{
			before_Tet_i = b4; 
			before_Tet_j = b3;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{
			if (flag_for_initial_V[b9] == -1) 
			{
				initial_V_to_target_V_ID[b9] = sur_ctp_cout; 
				my_target_V.row(sur_ctp_cout) = initial_V.row(b9); 
				hmap[toIndex] = sur_ctp_cout;  
				sur_ctp_cout++;

				flag_for_initial_V[b9] = 1; 

			}



		}
		else 
		{
			if (flag_for_initial_V[b9] == -1) 
			{
				initial_V_to_target_V_ID[b9] = interior_ctp_cout;
				my_target_V.row(interior_ctp_cout) = initial_V.row(b9);
				if (is_interior_linear_tet) 
				{
					my_target_V.row(interior_ctp_cout) = (initial_V.row(b3) + initial_V.row(b4)) / 2;
				}
				interior_ctp_cout++;

				flag_for_initial_V[b9] = 3; 
			}


		}

		//------------------------ 
		if (b2 > b4)
		{
			before_Tet_i = b2;
			before_Tet_j = b4;
		}
		else
		{
			before_Tet_i = b4; 
			before_Tet_j = b2;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);

		if (hmap.find(toIndex) != hmap.end()) 
		{
			if (flag_for_initial_V[b10] == -1) 
			{
				initial_V_to_target_V_ID[b10] = sur_ctp_cout; 
				my_target_V.row(sur_ctp_cout) = initial_V.row(b10); 
				hmap[toIndex] = sur_ctp_cout; 
				sur_ctp_cout++;

				flag_for_initial_V[b10] = 1; 
				  
			}



		}
		else 
		{
			if (flag_for_initial_V[b10] == -1) 
			{
				initial_V_to_target_V_ID[b10] = interior_ctp_cout;
				my_target_V.row(interior_ctp_cout) = initial_V.row(b10);
				if (is_interior_linear_tet) 
				{
					my_target_V.row(interior_ctp_cout) = (initial_V.row(b2) + initial_V.row(b4)) / 2;
				}
				interior_ctp_cout++;

				flag_for_initial_V[b10] = 3; 
			}


		}

		 

		  
		//------------------------ 
		if (flag_for_initial_V[b1] == 0) 
		{
			 
		}
		else  
		{
			if (flag_for_initial_V[b1] == -1) 
			{
				initial_V_to_target_V_ID[b1] = interior_ver_cout;
				my_target_V.row(interior_ver_cout) = initial_V.row(b1);
				interior_ver_cout++;

				flag_for_initial_V[b1] = 2; 
			}
		}

		//----------------------- 
		if (flag_for_initial_V[b2] == 0) 
		{
			 
		}
		else 
		{
			if (flag_for_initial_V[b2] == -1) 
			{
				initial_V_to_target_V_ID[b2] = interior_ver_cout;
				my_target_V.row(interior_ver_cout) = initial_V.row(b2);
				interior_ver_cout++;

				flag_for_initial_V[b2] = 2; 
			}
		}

		//---------------------- 
		if (flag_for_initial_V[b3] == 0) 
		{
			 
		}
		else  
		{
			if (flag_for_initial_V[b3] == -1) 
			{
				initial_V_to_target_V_ID[b3] = interior_ver_cout;
				my_target_V.row(interior_ver_cout) = initial_V.row(b3);
				interior_ver_cout++;

				flag_for_initial_V[b3] = 2; 
			}
		}

		//----------------------- 
		if (flag_for_initial_V[b4] == 0) 
		{
			 
		}
		else  
		{
			if (flag_for_initial_V[b4] == -1) 
			{
				initial_V_to_target_V_ID[b4] = interior_ver_cout;
				my_target_V.row(interior_ver_cout) = initial_V.row(b4);
				interior_ver_cout++;

				flag_for_initial_V[b4] = 2; 
			}
		}

	}

	 
	for (int i = 0; i < sur_tri_num; i++)
	{
		int b0 = before_sur_Tri(i, 0);
		int b1 = before_sur_Tri(i, 1);
		int b2 = before_sur_Tri(i, 2);

		if (b0 > b1) 
		{
			before_Tet_i = b0;
			before_Tet_j = b1;
		}
		else
		{
			before_Tet_i = b1; 
			before_Tet_j = b0;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);
		if (hmap.find(toIndex) == hmap.end()) std::cout << "========================== Error: hmap.find(toIndex)==hmap.end() ===================" << std::endl; 
		my_sur_Tri(i, 3) = hmap[toIndex];

		//------------------------------------------ 
		if (b1 > b2)
		{
			before_Tet_i = b1;
			before_Tet_j = b2;
		}
		else
		{
			before_Tet_i = b2;
			before_Tet_j = b1;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);
		if (hmap.find(toIndex) == hmap.end()) std::cout << "========================== Error: hmap.find(toIndex)==hmap.end() ===================" << std::endl;
		my_sur_Tri(i, 4) = hmap[toIndex];

		//------------------------------------------ 
		if (b2 > b0) 
		{
			before_Tet_i = b2;
			before_Tet_j = b0;
		}
		else
		{
			before_Tet_i = b0;
			before_Tet_j = b2;
		}
		toIndex = Lower_tri_ijtoIndex(before_Tet_i, before_Tet_j, Lower_tri_n);
		if (hmap.find(toIndex) == hmap.end()) std::cout << "========================== Error: hmap.find(toIndex)==hmap.end() ===================" << std::endl;
		my_sur_Tri(i, 5) = hmap[toIndex];

	}

 
	for (int i = 0; i < tet_num; i++)
	{
		int b1 =  before_volume_Tet(i, 0);
		int b2 =  before_volume_Tet(i, 1);
		int b3 =  before_volume_Tet(i, 2);
		int b4 =  before_volume_Tet(i, 3);
		int b5 =  before_volume_Tet(i, 4);
		int b6 =  before_volume_Tet(i, 5);
		int b7 =  before_volume_Tet(i, 6);
		int b8 =  before_volume_Tet(i, 7);
		int b9 =  before_volume_Tet(i, 8);
		int b10 = before_volume_Tet(i, 9);

		my_volume_Tet(i, 0) = initial_V_to_target_V_ID[b1 ]; 
		my_volume_Tet(i, 1) = initial_V_to_target_V_ID[b2 ];
		my_volume_Tet(i, 2) = initial_V_to_target_V_ID[b3 ];
		my_volume_Tet(i, 3) = initial_V_to_target_V_ID[b4 ];
		my_volume_Tet(i, 4) = initial_V_to_target_V_ID[b5 ];
		my_volume_Tet(i, 5) = initial_V_to_target_V_ID[b6 ];
		my_volume_Tet(i, 6) = initial_V_to_target_V_ID[b7 ];
		my_volume_Tet(i, 7) = initial_V_to_target_V_ID[b8 ];
		my_volume_Tet(i, 8) = initial_V_to_target_V_ID[b9 ];
		my_volume_Tet(i, 9) = initial_V_to_target_V_ID[b10];
	}

	 


	 
	out << toal_v_num << '\n';
	out << (sur_ver_num+sur_ctp_num) << '\n';
	out << sur_ver_num << '\n';
	for (int i = 0; i < sur_ver_num; i++)
	{
		out << my_target_V(i, 0) << "  " << my_target_V(i, 1) << " " << my_target_V(i, 2) << '\n';
	}
	for (int i = sur_ver_num; i < sur_ver_num + sur_ctp_num; i++)
	{
		out << my_target_V(i, 0) << "  " << my_target_V(i, 1) << " " << my_target_V(i, 2) << '\n';
	}
	out <<(interior_ver_num+interior_ctp_num)<< '\n';
	out << interior_ver_num << '\n';
	std::cout << "toal_v_num is: " << toal_v_num << std::endl;
	for (int i = sur_ver_num + sur_ctp_num; i < toal_v_num; i++)
	{
		out << my_target_V(i, 0) << "  " << my_target_V(i, 1) << " " << my_target_V(i, 2) << '\n';
	}

	out << (sur_tri_num + tet_num) << '\n';
	out << sur_tri_num << '\n';
	for (int i = 0; i < sur_tri_num; i++)
	{
		int b0 = my_sur_Tri(i, 0)+1; 
		int b1 = my_sur_Tri(i, 1)+1;
		int b2 = my_sur_Tri(i, 2)+1;
		int b3 = my_sur_Tri(i, 3)+1;
		int b4 = my_sur_Tri(i, 4)+1;
		int b5 = my_sur_Tri(i, 5)+1;

		out << b0 << " " << b1 << " " << b2 << " " << b3 << " " << b4 << " " << b5 << '\n';
	}

	out << tet_num << '\n';
	for (int i = 0; i < tet_num; i++)
	{
		int b1 =  my_volume_Tet(i, 0)+1; 
		int b2 =  my_volume_Tet(i, 1)+1;
		int b3 =  my_volume_Tet(i, 2)+1;
		int b4 =  my_volume_Tet(i, 3)+1;
		int b5 =  my_volume_Tet(i, 4)+1;
		int b6 =  my_volume_Tet(i, 5)+1;
		int b7 =  my_volume_Tet(i, 6)+1;
		int b8 =  my_volume_Tet(i, 7)+1;
		int b9 =  my_volume_Tet(i, 8)+1;
		int b10 = my_volume_Tet(i, 9)+1;

		out << b1 << " " << b2 << " " << b3 << " " << b4 << " " << b5 << " " << b6 << " " << b7 << " " << b8 << " " << b9 << " " << b10 << '\n';
	}

	out << std::endl;
}

int Lower_tri_ijtoIndex(int i, int j, int n) 
{
	return i + j * n - j * (j - 1) / 2;
}
 
void write_3D_msh_Lagrange(std::string& filename, Bezier3D2d& d_, Eigen::VectorXd& position_of_mesh)
{
	std::ofstream out(filename);
	out.precision(16);

	/// Header
	out << "$MeshFormat"
		<< "\n"
		<< "4.1 0 " << std::to_string(sizeof(double)) << "\n"
		<< "$EndMeshFormat"
		<< "\n"
		<< std::endl;

	/// Nodes
	int toal_v_num = d_.toal_v_num;
	int sur_v_num = d_.sur_v_num;

	out << "$Nodes"
		<< "\n"
		<< indent(1) << "2 " << toal_v_num << " 1 " << toal_v_num << "\n"
		<< indent(1) << "2 1 0 " << sur_v_num << "\n";

	for (int id = offset(0, baseOffset); id < offset(sur_v_num, baseOffset); id++)
		out << indent(1) << id << "\n";

	Eigen::MatrixXd Lag_m_V;
	Lag_m_V.resize(toal_v_num, 3);

	Eigen::MatrixXd Bez_m_V;
	Bez_m_V.resize(toal_v_num, 3);

	 
	std::vector<bool> is_visited_V(toal_v_num, false);

	 
	for (int i = 0; i < toal_v_num; i++)
	{
		Bez_m_V(i, 0) = position_of_mesh[i];
		Bez_m_V(i, 1) = position_of_mesh[i + toal_v_num];
		Bez_m_V(i, 2) = position_of_mesh[i + 2 * toal_v_num];
	}

	 
	int b0, b1, b2, b3, b4, b5, b6, b7, b8, b9; 

	int tet_f_num = d_.tet_f_num;
	for (int i = 0; i < tet_f_num; i++)
	{
		b0 = d_.m_Volume_T(i, 0);
		b1 = d_.m_Volume_T(i, 1);
		b2 = d_.m_Volume_T(i, 2);
		b3 = d_.m_Volume_T(i, 3);
		b4 = d_.m_Volume_T(i, 4);
		b5 = d_.m_Volume_T(i, 5);
		b6 = d_.m_Volume_T(i, 6);
		b7 = d_.m_Volume_T(i, 7);
		b8 = d_.m_Volume_T(i, 8);
		b9 = d_.m_Volume_T(i, 9);

		 
		if (is_visited_V[b0] == false)
		{
			Lag_m_V.row(b0) = Bez_m_V.row(b0);
			is_visited_V[b0] = true;
		}

		if (is_visited_V[b3] == false)
		{
			Lag_m_V.row(b3) = Bez_m_V.row(b3);
			is_visited_V[b3] = true;
		}

		if (is_visited_V[b5] == false)
		{
			Lag_m_V.row(b5) = Bez_m_V.row(b5);
			is_visited_V[b5] = true;
		}

		if (is_visited_V[b9] == false)
		{
			Lag_m_V.row(b9) = Bez_m_V.row(b9);
			is_visited_V[b9] = true;
		}

		 
		if (is_visited_V[b1] == false)
		{
			Lag_m_V.row(b1) = Bez_m_V.row(b1) / 2 + Bez_m_V.row(b0) / 4 + Bez_m_V.row(b3) / 4;
			 
			is_visited_V[b1] = true;
		}

		if (is_visited_V[b4] == false)
		{
			Lag_m_V.row(b4) = Bez_m_V.row(b4) / 2 + Bez_m_V.row(b3) / 4 + Bez_m_V.row(b5) / 4;
			 
			is_visited_V[b4] = true;
		}

		if (is_visited_V[b2] == false)
		{
			Lag_m_V.row(b2) = Bez_m_V.row(b2) / 2 + Bez_m_V.row(b0) / 4 + Bez_m_V.row(b5) / 4;
			 
			is_visited_V[b2] = true;
		}

		if (is_visited_V[b6] == false)
		{
			Lag_m_V.row(b6) = Bez_m_V.row(b6) / 2 + Bez_m_V.row(b0) / 4 + Bez_m_V.row(b9) / 4;
			 
			is_visited_V[b6] = true;
		}

		if (is_visited_V[b8] == false)
		{
			Lag_m_V.row(b8) = Bez_m_V.row(b8) / 2 + Bez_m_V.row(b5) / 4 + Bez_m_V.row(b9) / 4;
			 
			is_visited_V[b8] = true;
		}

		if (is_visited_V[b7] == false)
		{
			Lag_m_V.row(b7) = Bez_m_V.row(b7) / 2 + Bez_m_V.row(b3) / 4 + Bez_m_V.row(b9) / 4;
			 
			is_visited_V[b7] = true;
		}
	}
	
	 
	for (int i = 0; i < sur_v_num; i++)
	{

		out << Lag_m_V(i,0) << " " << Lag_m_V(i, 1) << " " << Lag_m_V(i, 2) << " " << "\n";

	}

	int vol_v_num = d_.vol_v_num;
	out << indent(1) << "3 1 0 " << vol_v_num << '\n';

	for (int id = offset(sur_v_num, baseOffset); id < offset(toal_v_num, baseOffset); id++)
		out << indent(1) << id << "\n";

	for (int i = 0; i < vol_v_num; i++)
	{
		out << Lag_m_V(i+ sur_v_num, 0) << " " << Lag_m_V(i + sur_v_num, 1) << " " << Lag_m_V(i + sur_v_num, 2) << " " << "\n";

	}

	out << "$EndNodes"
		<< "\n";

	/// Elements
	int toal_f_num = d_.toal_f_num;
	int tri_f_num = d_.tri_f_num;

	out << "$Elements"
		<< "\n"
		<< indent(1) << "2 " << toal_f_num << " 1 " << toal_f_num << "\n"
		<< indent(1) << "2 1 " << 9 << " " << tri_f_num << "\n";

	for (int i = 0; i < tri_f_num; i++)
	{
		b0 = d_.m_Sur_T(i, 0);
		b1 = d_.m_Sur_T(i, 1);
		b2 = d_.m_Sur_T(i, 2);
		b3 = d_.m_Sur_T(i, 3);
		b4 = d_.m_Sur_T(i, 4);
		b5 = d_.m_Sur_T(i, 5);

		out << indent(1) << offset(i, baseOffset);
		out << " " << (b0 + baseOffset) << " " << (b3 + baseOffset) << " " << (b5 + baseOffset) <<
			" " << (b1 + baseOffset) << " " << (b4 + baseOffset) << " " << (b2 + baseOffset) << '\n';
	}

	out << indent(1) << "3 1 " << 11 << " " << tet_f_num << "\n";
	for (int i = 0; i < tet_f_num; i++)
	{
		b0 = d_.m_Volume_T(i, 0);
		b1 = d_.m_Volume_T(i, 1);
		b2 = d_.m_Volume_T(i, 2);
		b3 = d_.m_Volume_T(i, 3);
		b4 = d_.m_Volume_T(i, 4);
		b5 = d_.m_Volume_T(i, 5);
		b6 = d_.m_Volume_T(i, 6);
		b7 = d_.m_Volume_T(i, 7);
		b8 = d_.m_Volume_T(i, 8);
		b9 = d_.m_Volume_T(i, 9);

		out << indent(1) << offset(i + tri_f_num, baseOffset);
		out << " " << (b0 + baseOffset) << " " << (b3 + baseOffset) << " " << (b5 + baseOffset) << " " << (b9 + baseOffset) <<
			" " << (b1 + baseOffset) << " " << (b4 + baseOffset) << " " << (b2 + baseOffset) << " " << (b6 + baseOffset) <<
			" " << (b8 + baseOffset) << " " << (b7 + baseOffset) << '\n';
	}

	out << "$EndElements"
		<< "\n"
		<< std::endl;

	out << std::endl;

}

 void write_3D_msh(std::string& filename, Bezier3D2d& d_, Eigen::VectorXd& position_of_mesh)
{
	std::ofstream out(filename);
	out.precision(10);

	/// Header
	out << "$MeshFormat"
		<< "\n"
		<< "4.1 0 " << std::to_string(sizeof(double)) << "\n"
		<< "$EndMeshFormat"
		<< "\n"
		<< std::endl;

	/// Nodes
	int toal_v_num = d_.toal_v_num;
	int sur_v_num = d_.sur_v_num;

	out << "$Nodes"
		<< "\n"
		<< indent(1) << "2 " << toal_v_num << " 1 " << toal_v_num << "\n"
		<< indent(1) << "2 1 0 " << sur_v_num << "\n";

	for (int id = offset(0, baseOffset); id < offset(sur_v_num, baseOffset); id++)
		out << indent(1) << id << "\n";

	for (int i = 0; i < sur_v_num; i++)
	{

		out << position_of_mesh[i] << " " << position_of_mesh[i + toal_v_num] << " " << position_of_mesh[i + 2 * toal_v_num] << " " << "\n";

	}

	int vol_v_num = d_.vol_v_num;
	out << indent(1) << "3 1 0 " << vol_v_num << '\n';

	for (int id = offset(sur_v_num, baseOffset); id < offset(toal_v_num, baseOffset); id++)
		out << indent(1) << id << "\n";

	for (int i = 0; i < vol_v_num; i++)
	{
		out << position_of_mesh[i + sur_v_num] << " " << position_of_mesh[i + sur_v_num + toal_v_num] << " " << position_of_mesh[i + sur_v_num + 2 * toal_v_num] << " " << "\n";
	}

	out << "$EndNodes"
		<< "\n";

	/// Elements
	int toal_f_num = d_.toal_f_num;
	int tri_f_num = d_.tri_f_num;

	out << "$Elements"
		<< "\n"
		<< indent(1) << "2 " << toal_f_num << " 1 " << toal_f_num << "\n"
		<< indent(1) << "2 1 " << 9 << " " << tri_f_num << "\n";

	int b0, b1, b2, b3, b4, b5, b6, b7, b8, b9;
	for (int i = 0; i < tri_f_num; i++)
	{
		b0 = d_.m_Sur_T(i, 0);
		b1 = d_.m_Sur_T(i, 1);
		b2 = d_.m_Sur_T(i, 2);
		b3 = d_.m_Sur_T(i, 3);
		b4 = d_.m_Sur_T(i, 4);
		b5 = d_.m_Sur_T(i, 5);

		out << indent(1) << offset(i, baseOffset);
		out << " " << (b0 + baseOffset) << " " << (b3 + baseOffset) << " " << (b5 + baseOffset) <<
			" " << (b1 + baseOffset) << " " << (b4 + baseOffset) << " " << (b2 + baseOffset) << '\n';
	}

	int tet_f_num = d_.tet_f_num;
	out<< indent(1) <<"3 1 "<<11<<" "<< tet_f_num << "\n";
	for (int i = 0; i < tet_f_num; i++)
	{
		b0 = d_.m_Volume_T(i, 0);
		b1 = d_.m_Volume_T(i, 1);
		b2 = d_.m_Volume_T(i, 2);
		b3 = d_.m_Volume_T(i, 3);
		b4 = d_.m_Volume_T(i, 4);
		b5 = d_.m_Volume_T(i, 5);
		b6 = d_.m_Volume_T(i, 6);
		b7 = d_.m_Volume_T(i, 7);
		b8 = d_.m_Volume_T(i, 8);
		b9 = d_.m_Volume_T(i, 9);

		out << indent(1) << offset(i+ tri_f_num, baseOffset);
		out << " " << (b0 + baseOffset) << " " << (b3 + baseOffset) << " " << (b5 + baseOffset) << " " << (b9 + baseOffset) <<
			" " << (b1 + baseOffset) << " " << (b4 + baseOffset) << " " << (b2 + baseOffset) << " " << (b6 + baseOffset) <<
			" " << (b8 + baseOffset) << " " << (b7 + baseOffset) << '\n';
	}

	out << "$EndElements"
		<< "\n"
		<< std::endl;

	out << std::endl;
}


 
void write_curve_mesh(std::string& filename, Bezier3D2d& d_, Eigen::VectorXd& position_of_mesh)
{
	std::ofstream out(filename);
	out.precision(16);

	int toal_v_num = d_.toal_v_num;
	out << toal_v_num << '\n';

	int sur_v_num = d_.sur_v_num;
	out << sur_v_num << '\n';

	int sur_ver_num = d_.sur_ver_num;
	out << sur_ver_num << '\n';

	for (int i = 0; i < sur_v_num; i++)
	{

		out << position_of_mesh[i] << " " << position_of_mesh[i + toal_v_num] << " " << position_of_mesh[i + 2 * toal_v_num] << " " << "\n";

	}

	int vol_v_num = d_.vol_v_num;
	out << d_.vol_v_num << '\n';

	int vol_ver_num = d_.vol_ver_num;
	out << d_.vol_ver_num << '\n';

	//int index = sur_v_num;
	for (int i = 0; i < vol_v_num; i++)
	{
		out << position_of_mesh[i + sur_v_num] << " " << position_of_mesh[i + sur_v_num + toal_v_num] << " " << position_of_mesh[i + sur_v_num + 2 * toal_v_num] << " " << "\n";
	}

	int toal_f_num = d_.toal_f_num;
	out << d_.toal_f_num << '\n';

	int tri_f_num = d_.tri_f_num;
	out << tri_f_num << '\n';

	int baseOffset = 1;
	int b0, b1, b2, b3, b4, b5, b6, b7, b8, b9;
	for (int i = 0; i < tri_f_num; i++)
	{
		b0 = d_.m_Sur_T(i, 0);
		b1 = d_.m_Sur_T(i, 1);
		b2 = d_.m_Sur_T(i, 2);
		b3 = d_.m_Sur_T(i, 3);
		b4 = d_.m_Sur_T(i, 4);
		b5 = d_.m_Sur_T(i, 5);

		out << " " << (b0 + baseOffset) << " " << (b3 + baseOffset) << " " << (b5 + baseOffset) <<
			" " << (b1 + baseOffset) << " " << (b4 + baseOffset) << " " << (b2 + baseOffset) << '\n';


	}

	int tet_f_num = d_.tet_f_num;
	out << tet_f_num << '\n';
	for (int i = 0; i < tet_f_num; i++)
	{
		b0 = d_.m_Volume_T(i, 0);
		b1 = d_.m_Volume_T(i, 1);
		b2 = d_.m_Volume_T(i, 2);
		b3 = d_.m_Volume_T(i, 3);
		b4 = d_.m_Volume_T(i, 4);
		b5 = d_.m_Volume_T(i, 5);
		b6 = d_.m_Volume_T(i, 6);
		b7 = d_.m_Volume_T(i, 7);
		b8 = d_.m_Volume_T(i, 8);
		b9 = d_.m_Volume_T(i, 9);

		out << " " << (b0 + baseOffset) << " " << (b3 + baseOffset) << " " << (b5 + baseOffset) << " " << (b9 + baseOffset) <<
			  " "  << (b1 + baseOffset) << " " << (b4 + baseOffset) << " " << (b2 + baseOffset) << " " << (b6 + baseOffset) <<
			  " "  << (b8 + baseOffset) << " " << (b7 + baseOffset) << '\n';
	}
	out << std::endl;

}

 
void read_get_Data(Bezier3D2d& d_, std::string s)
{
	 
	std::cout << "================ read data =============" << std::endl;
	std::ifstream ifs(s);
	if (!ifs.is_open())
	{
		std::cerr << "Error: cannot load control points from file " << s << std::endl;
		return;
	}
	int toal_v_num;
	ifs>> toal_v_num;
	d_.toal_v_num = toal_v_num;
	d_.m_V.resize(toal_v_num, 3);
	Eigen::MatrixXd Lag_m_V;
	Lag_m_V.resize(toal_v_num, 3);

	int sur_v_num;
	ifs>> sur_v_num;
	d_.sur_v_num= sur_v_num;

	int sur_ver_num;
	ifs>> sur_ver_num;
	d_.sur_ver_num= sur_ver_num;

	for (int i = 0; i < sur_v_num; i++)
	{
		ifs >> Lag_m_V(i, 0) >> Lag_m_V(i, 1) >> Lag_m_V(i, 2);
	}

	int vol_v_num;
	ifs >> vol_v_num;
	d_.vol_v_num = vol_v_num;

	if ((sur_v_num + vol_v_num) != toal_v_num)
	{
		std::cout << "####################### Error v_num ##################" << std::endl;
	}

	int vol_ver_num;
	ifs >> vol_ver_num;
	d_.vol_ver_num = vol_ver_num;

	for (int i = sur_v_num; i < sur_v_num + vol_v_num; i++)
	{
		ifs >> Lag_m_V(i, 0) >> Lag_m_V(i, 1) >> Lag_m_V(i, 2);
	}
	 
	d_.m_V = Lag_m_V;
	 

	int toal_f_num;
	ifs>> toal_f_num;
	d_.toal_f_num = toal_f_num;

	int tri_f_num;
	ifs>> tri_f_num;
	d_.tri_f_num= tri_f_num;
	d_.m_Sur_T.resize(tri_f_num, 6);

	for (int i = 0; i < tri_f_num; i++)
	{
		 
		ifs >> d_.m_Sur_T(i, 0) >> d_.m_Sur_T(i, 3) >> d_.m_Sur_T(i, 5) >> d_.m_Sur_T(i, 1) >> d_.m_Sur_T(i, 4) >> d_.m_Sur_T(i, 2);
		for (size_t j = 0; j < 6; j++) 
		{
			d_.m_Sur_T(i, j) -= 1;
		}
	}

	 
	std::vector<bool> is_visited_Sur_V(sur_v_num, false);

	for (int i = 0; i < tri_f_num; i++)
	{
		int b0 = d_.m_Sur_T(i, 0); 
		int b1 = d_.m_Sur_T(i, 1);
		int b2 = d_.m_Sur_T(i, 2);
		int b3 = d_.m_Sur_T(i, 3);
		int b4 = d_.m_Sur_T(i, 4);
		int b5 = d_.m_Sur_T(i, 5);
		if (is_visited_Sur_V[b1] == false)
		{
			d_.m_V.row(b1) = 2 * Lag_m_V.row(b1) - Lag_m_V.row(b0) / 2 - Lag_m_V.row(b3) / 2;
			is_visited_Sur_V[b1] = true;
		}
		if (is_visited_Sur_V[b4] == false)
		{
			d_.m_V.row(b4) = 2 * Lag_m_V.row(b4) - Lag_m_V.row(b3) / 2 - Lag_m_V.row(b5) / 2;
			is_visited_Sur_V[b4] = true;
		}
		if (is_visited_Sur_V[b2] == false)
		{
			d_.m_V.row(b2) = 2 * Lag_m_V.row(b2) - Lag_m_V.row(b0) / 2 - Lag_m_V.row(b5) / 2;
			is_visited_Sur_V[b2] = true;
		}

	}


	int tet_f_num;
	ifs>> tet_f_num;
	d_.tet_f_num= tet_f_num;
	d_.m_Volume_T.resize(tet_f_num, 10);

	 
	for (int i = 0; i < tet_f_num; i++)
	{		
		 
		ifs >> d_.m_Volume_T(i, 0) >> d_.m_Volume_T(i, 3) >> d_.m_Volume_T(i, 5) >> d_.m_Volume_T(i, 9) >> d_.m_Volume_T(i, 1)
			>> d_.m_Volume_T(i, 4) >> d_.m_Volume_T(i, 2) >> d_.m_Volume_T(i, 6) >> d_.m_Volume_T(i, 8) >> d_.m_Volume_T(i, 7); 
		for (int j = 0; j < 10; j++) 
		{
			d_.m_Volume_T(i, j) -= 1;
		}

		 
		 
		 
	}

	ifs.close();

	 
}

 
void read_get_Data_for_Bezier(Bezier3D2d& d_, std::string s)

{
	 
	std::cout << "================ read data =============" << std::endl;
	std::ifstream ifs(s);
	if (!ifs.is_open())
	{
		std::cerr << "Error: cannot load control points from file " << s << std::endl;
		return;
	}
	int toal_v_num;
	ifs >> toal_v_num;
	d_.toal_v_num = toal_v_num;
	d_.m_V.resize(toal_v_num, 3);
	Eigen::MatrixXd Bez_m_V;
	Bez_m_V.resize(toal_v_num, 3);

	int sur_v_num;
	ifs >> sur_v_num;
	d_.sur_v_num = sur_v_num;

	int sur_ver_num;
	ifs >> sur_ver_num;
	d_.sur_ver_num = sur_ver_num;

	for (int i = 0; i < sur_v_num; i++)
	{
		ifs >> Bez_m_V(i, 0) >> Bez_m_V(i, 1) >> Bez_m_V(i, 2);
	}

	int vol_v_num;
	ifs >> vol_v_num;
	d_.vol_v_num = vol_v_num;

	if ((sur_v_num + vol_v_num) != toal_v_num)
	{
		std::cout << "####################### Error v_num ##################" << std::endl;
	}

	int vol_ver_num;
	ifs >> vol_ver_num;
	d_.vol_ver_num = vol_ver_num;

	for (int i = sur_v_num; i < sur_v_num + vol_v_num; i++)
	{
		ifs >> Bez_m_V(i, 0) >> Bez_m_V(i, 1) >> Bez_m_V(i, 2);
	}
	 
	d_.m_V = Bez_m_V;
	 
	int toal_f_num;
	ifs >> toal_f_num;
	d_.toal_f_num = toal_f_num;

	int tri_f_num;
	ifs >> tri_f_num;
	d_.tri_f_num = tri_f_num;
	d_.m_Sur_T.resize(tri_f_num, 6);

	for (int i = 0; i < tri_f_num; i++)
	{
		 
		ifs >> d_.m_Sur_T(i, 0) >> d_.m_Sur_T(i, 3) >> d_.m_Sur_T(i, 5) >> d_.m_Sur_T(i, 1) >> d_.m_Sur_T(i, 4) >> d_.m_Sur_T(i, 2);
		for (size_t j = 0; j < 6; j++) 
		{
			d_.m_Sur_T(i, j) -= 1;
		}
	}

	int tet_f_num;
	ifs >> tet_f_num;
	d_.tet_f_num = tet_f_num;
	d_.m_Volume_T.resize(tet_f_num, 10);

	 
	for (int i = 0; i < tet_f_num; i++)
	{
		 
		ifs >> d_.m_Volume_T(i, 0) >> d_.m_Volume_T(i, 3) >> d_.m_Volume_T(i, 5) >> d_.m_Volume_T(i, 9) >> d_.m_Volume_T(i, 1)
			>> d_.m_Volume_T(i, 4) >> d_.m_Volume_T(i, 2) >> d_.m_Volume_T(i, 6) >> d_.m_Volume_T(i, 8) >> d_.m_Volume_T(i, 7); 
		for (int j = 0; j < 10; j++) 
		{
			d_.m_Volume_T(i, j) -= 1;
		}
	}

	ifs.close();

	 
}

 
 void read_get_Data(Eigen::MatrixXd& target_V, std::string s)
{
	std::ifstream ifs(s);
	if (!ifs.is_open())
	{
		std::cerr << "################# Error: cannot load control points from file ######################" << s << std::endl;
		return;
	}
	int toal_v_num;
	ifs >> toal_v_num;
	target_V.resize(toal_v_num, 3);
	 


	int sur_v_num;
	ifs >> sur_v_num;	 

	int sur_ver_num;
	ifs >> sur_ver_num;
	 
	for (int i = 0; i < sur_v_num; i++)
	{
		ifs >> target_V(i, 0) >> target_V(i, 1) >> target_V(i, 2);
	}

	int vol_v_num;
	ifs >> vol_v_num;
	 
	if ((sur_v_num + vol_v_num) != toal_v_num)
	{
		std::cout << "####################### Error v_num ##################" << std::endl;
	}

	int vol_ver_num;
	ifs >> vol_ver_num;
	 
	for (int i = sur_v_num; i < sur_v_num + vol_v_num; i++)
	{
		ifs >> target_V(i, 0) >> target_V(i, 1) >> target_V(i, 2);
	}

	std::cout << "================= target read data is ok! =====================" << std::endl;
	ifs.close();
}


 