#pragma once
#include "../src/Validity/btet.hpp"
#include "../src/Validity/hocgv.hpp"
#include <iostream>
#include <vector>
#include <algorithm> // std::shuffle
#include <numeric>
#include <random> 
namespace CABT
{
	//comparison with hocgv
	namespace exp1
	{
		void reset_filename();
		void read_index(std::vector<int>& index);
		template<typename T>
		void shuffle_vector(std::vector<T>& vec) {
			// ���������������
			std::random_device rd;   // ����豸���������ӣ�
			std::mt19937 g(rd());    // ��������������棨÷ɭ��ת����

			// ʹ�� std::shuffle ���� vector �е�Ԫ��
			std::shuffle(vec.begin(), vec.end(), g);
		}
		void generate_test_data();
		void compute_exact_collision_time(double threshold = 1e-4);
		void compute_mymethod_time();
		void compute_conservative_threshold();
		void compute_hocgvstep_with_threshold();
		void run_exp1();
	}

	namespace exp2
	{
		void run_morphing(std::vector<mat3_10>& val, std::vector<mat3_10>& dir, double& init_time);
	}

	namespace exp3
	{
		void compute_mymethod_time();
		void run_exp3();
	}
}